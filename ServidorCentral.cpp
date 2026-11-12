#include "ServidorCentral.h"
#include "Registro.h"   // mtx_consola, el mismo mutex de consola de todo el programa
#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>

ServidorCentral::ServidorCentral() : socketEscucha(INVALID_SOCKET) {}

// el destructor cierra el socket de escucha si quedo abierto
ServidorCentral::~ServidorCentral() {
    if (socketEscucha != INVALID_SOCKET) {
        cerrarSocket(socketEscucha);
        socketEscucha = INVALID_SOCKET;
    }
}

void ServidorCentral::iniciar() {

    if (!iniciarRed()) {
        throw std::runtime_error("Fallo en paso: iniciarRed()");
    }

    socketEscucha = socket(AF_INET, SOCK_STREAM, 0); // socket TCP
    if (socketEscucha == INVALID_SOCKET) {
        throw std::runtime_error("Fallo en paso: socket()");
    }

    sockaddr_in direccionServidor;
    std::memset(&direccionServidor, 0, sizeof(direccionServidor));
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = INADDR_ANY;
    direccionServidor.sin_port = htons(PUERTO_TCP); // puerto fijo 5000

    if (bind(socketEscucha, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == SOCKET_ERROR) {
        cerrarSocket(socketEscucha);
        socketEscucha = INVALID_SOCKET;
        throw std::runtime_error("Fallo en paso: bind()");
    }

    if (listen(socketEscucha, SOMAXCONN) == SOCKET_ERROR) {
        cerrarSocket(socketEscucha);
        socketEscucha = INVALID_SOCKET;
        throw std::runtime_error("Fallo en paso: listen()");
    }

    std::lock_guard<std::mutex> lock(mtx_consola);
    std::cout << "[ServidorCentral] Servidor TCP iniciado correctamente en el puerto " << PUERTO_TCP << std::endl;
}

void ServidorCentral::aceptarClientes() {
    std::vector<std::thread> hilosClientes;

    {
        std::lock_guard<std::mutex> lock(mtx_consola);
        std::cout << "[ServidorCentral] Esperando hasta " << MAX_CLIENTES << " conexiones de clientes..." << std::endl;
    }

    for (int i = 0; i < MAX_CLIENTES; ++i) {
        // select espera hasta ESPERA_ACCEPT_SEG a que llegue alguien. Sin esto,
        // si un cliente falla, el accept se queda esperando para siempre y el join del main nunca termina
        fd_set conjunto;
        FD_ZERO(&conjunto);
        FD_SET(socketEscucha, &conjunto);
        timeval espera;
        espera.tv_sec = ESPERA_ACCEPT_SEG;
        espera.tv_usec = 0;
        int listos = select((int)socketEscucha + 1, &conjunto, nullptr, nullptr, &espera);
        if (listos <= 0) {
            std::lock_guard<std::mutex> lock(mtx_consola);
            std::cerr << "[ServidorCentral] No llegaron mas clientes en " << ESPERA_ACCEPT_SEG
                      << " s, se dejan de aceptar conexiones" << std::endl;
            break;
        }

        sockaddr_in direccionCliente;
#ifdef _WIN32
        int tamDireccion = sizeof(direccionCliente);
#else
        socklen_t tamDireccion = sizeof(direccionCliente);
#endif

        SocketType socketCliente = accept(socketEscucha, (struct sockaddr*)&direccionCliente, &tamDireccion);

        if (socketCliente == INVALID_SOCKET) {
            std::lock_guard<std::mutex> lock(mtx_consola);
            std::cerr << "[ServidorCentral] Error al aceptar la conexión del cliente " << (i + 1) << std::endl;
            continue;
        }

        // un hilo por cliente, asi el servidor sigue aceptando mientras atiende
        hilosClientes.push_back(std::thread(&ServidorCentral::atenderCliente, this, socketCliente));
    }

    for (auto& t : hilosClientes) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::lock_guard<std::mutex> lock(mtx_consola);
    std::cout << "[ServidorCentral] Se completó la atención de todos los clientes (.join ejecutado)." << std::endl;
}

void ServidorCentral::atenderCliente(SocketType cliente) {
    try {
        char buffer[512];
        int bytesRecibidos = recv(cliente, buffer, sizeof(buffer) - 1, 0);

        if (bytesRecibidos <= 0) {
            throw std::runtime_error("Cliente desconectado");
        }

        buffer[bytesRecibidos] = '\0';

        // Deserializacion: se parte la trama TIPO|ID|IP|VALOR por cada '|'
        std::string trama(buffer);
        std::vector<std::string> campos;
        std::size_t inicio = 0;
        std::size_t pos = trama.find('|');
        while (pos != std::string::npos) {
            campos.push_back(trama.substr(inicio, pos - inicio));
            inicio = pos + 1;
            pos = trama.find('|', inicio);
        }
        campos.push_back(trama.substr(inicio));   // el ultimo campo no tiene | despues
        if (campos.size() != 4) {
            throw std::runtime_error(std::string("Trama mal formada: ") + buffer);
        }

        {
            std::lock_guard<std::mutex> lock(mtx_consola);
            std::cout << "[SERVIDOR - HILO " << std::this_thread::get_id() << "] Trama recibida: " << buffer << std::endl;
            std::cout << "      -> Tipo: " << campos[0] << " | ID: " << campos[1]
                      << " | IP: " << campos[2] << " | Valor: " << campos[3] << std::endl;
        }

        // simulamos que procesar la trama se demora un poco, asi se ve que
        // los hilos de los clientes estan atendiendose al mismo tiempo
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        if (send(cliente, "ACK", 3, 0) == SOCKET_ERROR) {
            throw std::runtime_error("No se pudo enviar el ACK al cliente");
        }
    }
    catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(mtx_consola);
        std::cerr << "[SERVIDOR - EXCEPCION EN HILO CLIENTE]: " << e.what() << std::endl;
    }

    cerrarSocket(cliente); // fuera del try para que se cierre aunque haya error
}

void iniciarServidorTCP() {
    try {
        ServidorCentral servidor;
        servidor.iniciar();
        servidor.aceptarClientes();
    }
    catch (const std::runtime_error& e) {
        std::lock_guard<std::mutex> lock(mtx_consola);
        std::cerr << "[EXCEPCION CAPTURADA EN SERVIDOR TCP]: " << e.what() << std::endl;
    }
    finalizarRed();
}
