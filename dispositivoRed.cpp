#include "DispositivoRed.h"

using namespace std;

DispositivoRed::DispositivoRed (string direccionIP, double anchoBandaMbps)
    : direccionIP(direccionIP), anchoBandaMbps(anchoBandaMbps){
}

string DispositivoRed::getDireccionIP() const {
    return direccionIP; }
