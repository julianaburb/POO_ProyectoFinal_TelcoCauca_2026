#include "SwitchFibra.h"
#include "Registro.h"
#include <thread>
#include <chrono>

SwitchFibra::SwitchFibra(const std::string& _id, int _velocidad)
    : DispositivoComunicacion(_id, "Switch Fibra Optica"), velocidadGbps(_velocidad) {}

void SwitchFibra::transmitir() {
    // Logica de conmutacion optica de alta velocidad
    registrarEventoSeguro(tipo + " " + id + " conmutando trafico optico a "
                          + std::to_string(velocidadGbps) + " Gbps");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
