#include "ConfigRed.h"     // de aqui salen IP_SERVIDOR, PUERTO_TCP, SocketType y las funciones de red
#include <stdexcept>
#include "ClienteTCP.h"

//Cliente TCP (estacion base), el orden es socket -> connect -> send -> recv -> cerrar
void enviarTramaTCP(const std::string& trama) {
    if (!iniciarRed())
        throw std::runtime_error("TCP cliente: no se pudo iniciar la red");

    //SOCK_STREAM = TCP, con conexion (en UDP seria SOCK_DGRAM)
    SocketType s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        finalizarRed();
        throw std::runtime_error("TCP cliente: no se pudo crear el socket");
    }

    //Direccion del ServidorCentral
    sockaddr_in servidor{};
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PUERTO_TCP);
    servidor.sin_addr.s_addr = inet_addr(IP_SERVIDOR.c_str());

    if (connect(s, (sockaddr*)&servidor, sizeof(servidor)) == SOCKET_ERROR) {  //connect es "llamar" al servidor
        cerrarSocket(s);
        finalizarRed();
        throw std::runtime_error("TCP cliente: no se pudo conectar al ServidorCentral");
    }

    send(s, trama.c_str(), (int)trama.size(), 0);
    std::cout << "[TCP cliente] Trama enviada: " << trama << std::endl; //Se envia la trama serializada con el formato TIPO|ID|IP|VALOR

    char buffer[64];
    int bytes = recv(s, buffer, sizeof(buffer) - 1, 0);  //Esperamos la respuesta (ACK) recv, devuelve 0 si el servidor cierra la conexion
    if (bytes <= 0) {
        cerrarSocket(s);
        finalizarRed();
        throw std::runtime_error("TCP cliente: el servidor no respondio");
    }
    buffer[bytes] = '\0';   //terminador nulo antes de imprimir
    std::cout << "[TCP cliente] Respuesta del servidor: " << buffer << std::endl;

    cerrarSocket(s);
    finalizarRed();
}