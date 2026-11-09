#include "DispositivoRed.h"

using namespace std;

DispositivoRed:: DispositivoRed (std::string direccionIP, std::string direccionMAC, bool estadoOperativo) : direccionIP(direccionIP), 
direccionMAC(direccionMAC), estadoOperativo(estadoOperativo) {
}

string DispositivoRed::getDireccionIP() const {
    return direccionIP; }
