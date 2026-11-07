#include "GatewayLoRa.h"
#include "Registro.h"
#include <thread>
#include <chrono>
#include <sstream>

GatewayLoRa::GatewayLoRa(const std::string& _id, float _freq)
    : DispositivoComunicacion(_id, "Gateway LoRaWAN"), frecuenciaMHz(_freq) {}

void GatewayLoRa::transmitir() {
    // Logica de transmision de larga distancia y bajo consumo
    // uso ostringstream porque to_string con float saca como 868.099976
    std::ostringstream msg;
    msg << tipo << " " << id << " enviando paquete de largo alcance a "
        << frecuenciaMHz << " MHz";
    registrarEventoSeguro(msg.str());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
