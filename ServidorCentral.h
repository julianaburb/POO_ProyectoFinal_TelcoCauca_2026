#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H

#include <vector>
#include <thread>
#include <mutex>
#include <stdexcept>
#include "ConfigRed.h"

const int MAX_CLIENTES = 3;          // clientes que atiende en la demo
const int ESPERA_ACCEPT_SEG = 5;     // si en 5 s no llega nadie, el servidor deja de esperar

class ServidorCentral {
private:
    SocketType socketEscucha;

public:
    ServidorCentral();
    ~ServidorCentral();

    void iniciar();
    void aceptarClientes();
    void atenderCliente(SocketType cliente); // corre en un hilo por cada cliente
};

void iniciarServidorTCP(); // crea el servidor, lo inicia y acepta clientes (se lanza en un hilo desde el main)

#endif
