#include "ConfigRed.h"     // va primero: trae winsock en Windows o sys/socket en Linux
#include <cstring>
#include <cerrno>
#include "TelemetriaUDP.h"

// Codigo del ultimo error de red (en Windows se pide distinto que en Linux)
static int ultimoErrorRed() {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

// ---------------------------------------------------------------------
// EMISOR (cliente UDP): sin bind ni connect, solo sendto hacia IP:puerto
// ---------------------------------------------------------------------
void enviarTelemetriaUDP(const NodoRedInteligente& nodo) {
    iniciarRed();

    SocketType s = socket(AF_INET, SOCK_DGRAM, 0);   // SOCK_DGRAM = UDP
    if (s == INVALID_SOCKET) {
        int err = ultimoErrorRed();
        finalizarRed();
        throw ExcepcionRedUDP("UDP: no se pudo crear el socket del emisor", err);
    }

    sockaddr_in destino{};
    destino.sin_family = AF_INET;
    destino.sin_port = htons(PUERTO_UDP);
    destino.sin_addr.s_addr = inet_addr(IP_SERVIDOR.c_str());

    // Serializacion binaria: copiamos los datos del objeto a la trama empaquetada
    TramaSensor trama{};
    trama.idNodo = nodo.getIdNodo();
    std::strncpy(trama.tipoSensor, nodo.getTipoSensor().c_str(), sizeof(trama.tipoSensor) - 1);
    trama.valorLectura = (float)nodo.getValorLectura();
    std::strncpy(trama.direccionIP, nodo.getDireccionIP().c_str(), sizeof(trama.direccionIP) - 1);

    sendto(s, reinterpret_cast<const char*>(&trama), sizeof(trama), 0,
           (sockaddr*)&destino, sizeof(destino));
    std::cout << "[UDP TX] Nodo " << trama.idNodo << " envio " << sizeof(trama)
              << " bytes (" << trama.tipoSensor << ": " << trama.valorLectura << ")" << std::endl;

    cerrarSocket(s);
    finalizarRed();
}

// ---------------------------------------------------------------------
// RECEPTOR (servidor UDP): bind obligatorio + timeout de 3 s en recvfrom
// ---------------------------------------------------------------------
void recibirTelemetriaUDP(int cantidad) {
    iniciarRed();

    SocketType s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        int err = ultimoErrorRed();
        finalizarRed();
        throw ExcepcionRedUDP("UDP: no se pudo crear el socket del receptor", err);
    }

    sockaddr_in local{};
    local.sin_family = AF_INET;
    local.sin_port = htons(PUERTO_UDP);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        int err = ultimoErrorRed();
        cerrarSocket(s);
        finalizarRed();
        throw ExcepcionRedUDP("UDP: fallo el bind, el puerto puede estar ocupado", err);
    }

    // Timeout de 3 s para que recvfrom no se quede bloqueado para siempre
#ifdef _WIN32
    DWORD timeout = 3000;                       // Windows: milisegundos
#else
    struct timeval timeout{3, 0};               // Linux: segundos, como en la diapositiva
#endif
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    std::cout << "[UDP RX] Escuchando en el puerto " << PUERTO_UDP
              << " (trama de " << sizeof(TramaSensor) << " bytes)..." << std::endl;

    for (int i = 0; i < cantidad; i++) {
        TramaSensor recibida{};
        sockaddr_in remitente{};
#ifdef _WIN32
        int tam = sizeof(remitente);
#else
        socklen_t tam = sizeof(remitente);
#endif
        int bytes = recvfrom(s, reinterpret_cast<char*>(&recibida), sizeof(recibida), 0,
                             (sockaddr*)&remitente, &tam);
        if (bytes == SOCKET_ERROR) {
            int err = ultimoErrorRed();
            cerrarSocket(s);
            finalizarRed();
            throw ExcepcionRedUDP("TIMEOUT o error: no se recibio datagrama en 3 s", err);
        }
        if (bytes == sizeof(TramaSensor)) {   // solo si llego completa
            std::cout << "[UDP RX] Nodo " << recibida.idNodo << " | IP " << recibida.direccionIP
                      << " | " << recibida.tipoSensor << ": " << recibida.valorLectura << std::endl;
        }
    }

    cerrarSocket(s);
    finalizarRed();
}