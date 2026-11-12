#include "ConfigRed.h"

bool iniciarRed() { //inicializar la red, en Windows se llama WSAStartup, en Linux no hace falta
#ifdef _WIN32
    WSADATA wsaData;
    int resultado = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (resultado != 0) {
        std::cerr << "[ConfigRed] Error al inicializar Winsock: " << resultado << std::endl;
        return false; 
    }
#endif
    return true;
}

void finalizarRed() { //libera los recursos globales de red cuando el programa termina
#ifdef _WIN32
    WSACleanup();
#endif
}

void cerrarSocket(SocketType s) {
#ifdef _WIN32
    closesocket(s);
#else
    close(s);
#endif
}