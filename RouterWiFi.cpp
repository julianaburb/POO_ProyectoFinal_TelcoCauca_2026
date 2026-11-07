#include "RouterWiFi.h"
#include "Registro.h"
#include <thread>
#include <chrono>

RouterWiFi::RouterWiFi(const std::string& _id, int _canales)
    : DispositivoComunicacion(_id, "Router WiFi 6"), canalesActivos(_canales) {}

void RouterWiFi::transmitir() {
    // Logica de transmision especifica sobre la banda de 5 GHz
    registrarEventoSeguro(tipo + " " + id + " transmitiendo en 5 GHz con "
                          + std::to_string(canalesActivos) + " canales activos");
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
}
