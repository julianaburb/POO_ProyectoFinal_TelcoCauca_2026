#ifndef CONFIGRED_H
#define CONFIGRED_H

#include <iostream>
#include <string>

// C++11 no trae sockets, entonces se incluyen los de Windows o los de Linux
// segun el sistema donde se compile
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef SOCKET SocketType;
#else
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <unistd.h>
    typedef int SocketType;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

// formato de las tramas: TIPO|ID|IP|VALOR

const std::string IP_SERVIDOR = "127.0.0.1";
const int PUERTO_TCP = 5000;
const int PUERTO_UDP = 5001;

bool iniciarRed();
void finalizarRed();
void cerrarSocket(SocketType s);

#endif
