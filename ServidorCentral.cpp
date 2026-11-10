#include "ServidorCentral.h"
#include <iostream>
#include <cstring>

ServidorCentral::ServidorCentral() : socketEscucha(INVALID_SOCKET) {}

// Destructor que aplica el patrón RAII liberando el socket de escucha
ServidorCentral::~ServidorCentral() {
    if (socketEscucha != INVALID_SOCKET) {
        cerrarSocket(socketEscucha);
        socketEscucha = INVALID_SOCKET;
    }
}

void ServidorCentral::iniciar() {
   
    if (!iniciarRed()) {
        throw std::runtime_error("Fallo en paso: iniciarRed()");
    } // 1. Inicializar el subsistema de red (WSAStartup / POSIX)

    socketEscucha = socket(AF_INET, SOCK_STREAM, 0);
    if (socketEscucha == INVALID_SOCKET) {
        throw std::runtime_error("Fallo en paso: socket()");
    }// 2. Creación del socket TCP

    sockaddr_in direccionServidor;
    std::memset(&direccionServidor, 0, sizeof(direccionServidor));
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = INADDR_ANY;
    direccionServidor.sin_port = htons(PUERTO_TCP); // 3. Configuración del puerto fijo y dirección (INADDR_ANY, PUERTO_TCP=5000)

    if (bind(socketEscucha, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == SOCKET_ERROR) {
        cerrarSocket(socketEscucha);
        socketEscucha = INVALID_SOCKET;
        throw std::runtime_error("Fallo en paso: bind()");
    }  // 4. Enlace del socket a la dirección y puerto (bind)

    if (listen(socketEscucha, SOMAXCONN) == SOCKET_ERROR) {
        cerrarSocket(socketEscucha);
        socketEscucha = INVALID_SOCKET;
        throw std::runtime_error("Fallo en paso: listen()");
    }// 5. Poner el socket en modo escucha (listen)
0
    std::cout << "[ServidorCentral] Servidor TCP iniciado correctamente en el puerto " << PUERTO_TCP << std::endl;
}

void ServidorCentral::aceptarClientes() {
    std::vector<std::thread> hilosClientes;

    std::cout << "[ServidorCentral] Esperando hasta " << MAX_CLIENTES << " conexiones de clientes..." << std::endl;

    for (int i = 0; i < MAX_CLIENTES; ++i) {
        sockaddr_in direccionCliente;
#ifdef _WIN32
        int tamDireccion = sizeof(direccionCliente);
#else
        socklen_t tamDireccion = sizeof(direccionCliente);
#endif

        // Aceptar conexión entrante (accept)
        SocketType socketCliente = accept(socketEscucha, (struct sockaddr*)&direccionCliente, &tamDireccion);

        if (socketCliente == INVALID_SOCKET) {
            std::lock_guard<std::mutex> lock(mtxConsolaServidor);
            std::cerr << "[ServidorCentral] Error al aceptar la conexión del cliente " << (i + 1) << std::endl;
            continue;
        }

        // Generar hilo dedicado por cliente pasando 'this' como puntero a la instancia
        hilosClientes.push_back(std::thread(&ServidorCentral::atenderCliente, this, socketCliente));
    }

    // Sincronización obligatoria (.join()) de todos los hilos al salir del bucle
    for (auto& t : hilosClientes) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "[ServidorCentral] Se completó la atención de todos los clientes (.join ejecutado)." << std::endl;
}

void ServidorCentral::atenderCliente(SocketType cliente) {
    try {
        char buffer[512];
        int bytesRecibidos = recv(cliente, buffer, sizeof(buffer) - 1, 0);

        if (bytesRecibidos <= 0) {
            throw std::runtime_error("Cliente desconectado");
        }

        buffer[bytesRecibidos] = '\0'; // Asegurar terminador de cadena

        // Registro protegido de la sección crítica mediante mutex (RAII)
        {
            std::lock_guard<std::mutex> lock(mtxConsolaServidor);
            std::cout << "[SERVIDOR - HILO " << std::this_thread::get_id() << "] Trama recibida: " << buffer << std::endl;
        }

        // Envío de respuesta ACK de confirmación al cliente
        send(cliente, "ACK", 3, 0);
    }
    catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(mtxConsolaServidor);
        std::cerr << "[SERVIDOR - EXCEPCION EN HILO CLIENTE]: " << e.what() << std::endl;
    }

    // Cierre del socket del cliente al finalizar la rutina (fuera del try)
    cerrarSocket(cliente);
}

void iniciarServidorTCP() {
    try {
        ServidorCentral servidor;
        servidor.iniciar();
        servidor.aceptarClientes();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[EXCEPCION CAPTURADA EN SERVIDOR TCP]: " << e.what() << std::endl;
    }
    finalizarRed();
}