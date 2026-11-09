#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H

#include <vector>
#include <thread>
#include <mutex>
#include <stdexcept>
#include "ConfigRed.h"

const int MAX_CLIENTES = 3; // Límite de conexiones p la demostración limpia

class ServidorCentral {
private:
    SocketType socketEscucha;
    std::mutex mtxConsolaServidor;

public:
    ServidorCentral();
    ~ServidorCentral();

    void iniciar();
    void aceptarClientes();
    void atenderCliente(SocketType cliente); //punto 5
};

void iniciarServidorTCP();// Función de la opción 5 del menú (iniciarServidorTCP)

#endif 