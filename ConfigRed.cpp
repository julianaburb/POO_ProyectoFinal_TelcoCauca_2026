#ifndef CONFIGRED_H
#define CONFIGRED_H

#include <iostream>
#include <string>

// Selección de cabeceras y tipos según el Sistema Operativo
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef SOCKET SocketType;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <unistd.h>
    typedef int SocketType;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

// FORMATO DE TRAMA DE TELEMETRÍA Y ESTADO: TIPO|ID|IP|VALOR

// Constantes globales de configuración de red
const std::string IP_SERVIDOR = "127.0.0.1";
const int PUERTO_TCP = 5000;
const int PUERTO_UDP = 5001;

// Funciones de abstracción de socket multiplataforma
bool iniciarRed();
void finalizarRed();
void cerrarSocket(SocketType s);

#endif