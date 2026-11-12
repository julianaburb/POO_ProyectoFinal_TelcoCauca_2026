#ifndef TELEMETRIAUDP_H
#define TELEMETRIAUDP_H
#include <cstdint>
#include <stdexcept>
#include <string>
#include "NodoRedInteligente.h"

// pack(1) para que el compilador no meta relleno entre campos y la trama mida 40 bytes
#pragma pack(push, 1)
struct TramaSensor {
    uint32_t idNodo;          // 4 bytes
    char tipoSensor[16];      // 16 bytes
    float valorLectura;       // 4 bytes
    char direccionIP[16];     // 16 bytes
};
#pragma pack(pop)

// excepcion para los errores de UDP, guarda el codigo de error del sistema
class ExcepcionRedUDP : public std::runtime_error {
private:
    int codigoError;
public:
    ExcepcionRedUDP(const std::string& msg, int err)
        : std::runtime_error(msg + " [Codigo: " + std::to_string(err) + "]"), codigoError(err) {}
    int getCodigoError() const { return codigoError; }
};

// emisor: arma la TramaSensor con los datos del nodo y la manda con sendto
void enviarTelemetriaUDP(const NodoRedInteligente& nodo);

// receptor: bind al puerto y recibe 'cantidad' tramas con recvfrom (timeout de 3 s)
void recibirTelemetriaUDP(int cantidad);

#endif
