#include "RouterWiFi.h"
#include <iostream>

RouterWiFi::RouterWiFi(const std::string& iP)
    : DispositivoComunicacion(iP) {}

void RouterWiFi::transmitir() {
    std::cout << "[RouterWiFi] Transmitiendo paquetes inalámbricos desde IP: " << iP << std::endl;
}

std::string RouterWiFi::serializar() const {
    return "ROUTERWIFI|ID-WIFI|" + iP + "|OK";
}