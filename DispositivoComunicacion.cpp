#include "DispositivoComunicacion.h"

DispositivoComunicacion::DispositivoComunicacion(const std::string& iP)
    : iP(iP) {}

std::string DispositivoComunicacion::getIp() const {
    return iP;
}