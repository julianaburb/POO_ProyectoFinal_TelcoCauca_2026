#include "DispositivoRed.h"
#include "ExcepcionNodoRed.h"
using namespace std;

DispositivoRed::DispositivoRed(const std::string& direccionIP, const std::string& direccionMAC, bool estadoOperativo)
    : direccionIP(direccionIP), direccionMAC(direccionMAC), estadoOperativo(estadoOperativo) {
    validarIP();
} // Valido la IP dentro del constructor porque es el unico momento por el que
// pasa todo dispositivo al crearse. Asi nos aseguramos de que nunca exista un
// DispositivoRed con la IP vacía: si la IP no sirve, el objeto ni siquiera se
// termina de construir y se lanza ExcepcionNodoRed de inmediato. Si lo dejáramos
// como un método aparte, habría que acordarse de llamarlo siempre, y el error
// podría aparecer mucho después, lejos de donde realmente se originó.

void DispositivoRed::validarIP() const {
    if (direccionIP.empty())
        throw ExcepcionNodoRed("Direccion IP invalida: la IP esta vacia");
}