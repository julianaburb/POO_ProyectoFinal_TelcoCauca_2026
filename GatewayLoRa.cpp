#include "GatewayLoRa.h"
#include <iostream>

GatewayLoRa::GatewayLoRa(const std::string& iP)
    : DispositivoComunicacion(iP) {}

void GatewayLoRa::transmitir() {
    std::cout << "[GatewayLoRa] Transmitiendo tramas LoRaWAN desde IP: " << iP << std::endl;
}

std::string GatewayLoRa::serializar() const {
    return "GATEWAYLORA|ID-LORA|" + iP + "|OK";
}