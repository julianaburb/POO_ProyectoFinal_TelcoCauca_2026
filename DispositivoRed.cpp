#include "DispositivoRed.h"
#include "ExcepcionNodoRed.h"

DispositivoRed::DispositivoRed(const std::string& direccionIP, const std::string& direccionMAC, bool estadoOperativo)
    : direccionIP(direccionIP), direccionMAC(direccionMAC), estadoOperativo(estadoOperativo) {
    validarIP(); // se valida aca para que no se pueda crear un dispositivo sin IP
}

void DispositivoRed::validarIP() const {
    if (direccionIP.empty())
        throw ExcepcionNodoRed("Direccion IP invalida: la IP esta vacia");
}
