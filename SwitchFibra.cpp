#include "SwitchFibra.h"
#include <iostream>

SwitchFibra::SwitchFibra(const std::string& iP)
    : DispositivoComunicacion(iP) {}

void SwitchFibra::transmitir() {
    std::cout << "[SwitchFibra] Conmutando paquetes ópticos desde IP: " << iP << std::endl;
}

std::string SwitchFibra::serializar() const {
    return "SWITCHFIBRA|ID-FIBRA|" + iP + "|OK";
}