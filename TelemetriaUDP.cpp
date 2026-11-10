#include <winsock2.h>      // sockets de Windows (equivale a sys/socket.h de Linux)
#include <iostream>
#include <cstring>
#include "TelemetriaUDP.h"

static const char* IP_DESTINO_UDP = "127.0.0.1";   // este mismo computador
static const int   PUERTO_TELEMETRIA = 9001;

// ---------------------------------------------------------------------
// EMISOR (cliente UDP): no necesita bind ni connect, Windows le asigna
// un puerto temporal solo. Llenamos la trama y la disparamos con sendto.
// ---------------------------------------------------------------------
void enviarTelemetriaUDP(const NodoRedInteligente& nodo) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);   // SOCK_DGRAM = UDP
    if (s == INVALID_SOCKET) {
        int err = WSAGetLastError();
        WSACleanup();
        throw ExcepcionRedUDP("UDP: no se pudo crear el socket del emisor", err);
    }

    sockaddr_in destino{};
    destino.sin_family = AF_INET;
    destino.sin_port = htons(PUERTO_TELEMETRIA);
    destino.sin_addr.s_addr = inet_addr(IP_DESTINO_UDP);

    // Serializacion binaria: pasamos los datos del objeto a la trama empaquetada
    TramaSensor trama{};
    trama.idNodo = nodo.getIdNodo();
    std::strncpy(trama.tipoSensor, nodo.getTipoSensor().c_str(), sizeof(trama.tipoSensor) - 1);
    trama.valorLectura = (float)nodo.getValorLectura();
    std::strncpy(trama.direccionIP, nodo.getDireccionIP().c_str(), sizeof(trama.direccionIP) - 1);

    // reinterpret_cast: tratamos la trama como un bloque de bytes para enviarla tal cual
    sendto(s, reinterpret_cast<const char*>(&trama), sizeof(trama), 0,
           (sockaddr*)&destino, sizeof(destino));
    std::cout << "[UDP TX] Nodo " << trama.idNodo << " envio " << sizeof(trama)
              << " bytes (" << trama.tipoSensor << ": " << trama.valorLectura << ")" << std::endl;

    closesocket(s);   // en Linux seria close(s)
    WSACleanup();
}

// ---------------------------------------------------------------------
// RECEPTOR (servidor UDP): bind es obligatorio para quedarse en el puerto.
// Le ponemos un timeout de 3 s para que recvfrom no se quede bloqueado
// para siempre si nadie envia nada (UDP no avisa si el emisor se cayo).
// ---------------------------------------------------------------------
void recibirTelemetriaUDP(int cantidad) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == INVALID_SOCKET) {
        int err = WSAGetLastError();
        WSACleanup();
        throw ExcepcionRedUDP("UDP: no se pudo crear el socket del receptor", err);
    }

    sockaddr_in local{};
    local.sin_family = AF_INET;
    local.sin_port = htons(PUERTO_TELEMETRIA);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        int err = WSAGetLastError();
        closesocket(s);
        WSACleanup();
        throw ExcepcionRedUDP("UDP: fallo el bind, el puerto puede estar ocupado", err);
    }

    // Timeout de 3 segundos (en Windows va en milisegundos)
    DWORD timeout = 3000;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    std::cout << "[UDP RX] Escuchando en el puerto " << PUERTO_TELEMETRIA
              << " (trama de " << sizeof(TramaSensor) << " bytes)..." << std::endl;

    for (int i = 0; i < cantidad; i++) {
        TramaSensor recibida{};
        sockaddr_in remitente{};
        int tam = sizeof(remitente);

        int bytes = recvfrom(s, reinterpret_cast<char*>(&recibida), sizeof(recibida), 0,
                             (sockaddr*)&remitente, &tam);
        if (bytes == SOCKET_ERROR) {
            int err = WSAGetLastError();
            closesocket(s);
            WSACleanup();
            if (err == WSAETIMEDOUT)
                throw ExcepcionRedUDP("TIMEOUT: no se recibio ningun datagrama en 3 s", err);
            throw ExcepcionRedUDP("Error al recibir con recvfrom", err);
        }
        // Solo aceptamos la trama si llego completa (los 40 bytes)
        if (bytes == sizeof(TramaSensor)) {
            std::cout << "[UDP RX] Nodo " << recibida.idNodo << " | IP " << recibida.direccionIP
                      << " | " << recibida.tipoSensor << ": " << recibida.valorLectura << std::endl;
        }
    }

    closesocket(s);
    WSACleanup();
}