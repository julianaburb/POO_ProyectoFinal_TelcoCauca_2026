#ifndef TELEMETRIAUDP_H
#define TELEMETRIAUDP_H
#include <cstdint>
#include <stdexcept>
#include <string>
#include "nodoRedInteligente.h"

// Trama binaria que viaja por UDP. Con #pragma pack(push, 1) el compilador
// no mete bytes de relleno (padding), asi la trama mide exactamente lo que suman
// sus campos: 4 + 16 + 4 + 16 = 40 bytes. Sin esto el sizeof podria cambiar.
#pragma pack(push, 1)
struct TramaSensor {
    uint32_t idNodo;          // 4 bytes
    char tipoSensor[16];      // 16 bytes
    float valorLectura;       // 4 bytes
    char direccionIP[16];     // 16 bytes
};
#pragma pack(pop)   // devolvemos la alineacion normal para el resto del codigo

// Excepcion propia para errores de red UDP, hereda de runtime_error como en clase.
// Guarda el codigo de error que devuelve Windows para saber que paso.
class ExcepcionRedUDP : public std::runtime_error {
private:
    int codigoError;
public:
    ExcepcionRedUDP(const std::string& msg, int err)
        : std::runtime_error(msg + " [Codigo: " + std::to_string(err) + "]"), codigoError(err) {}
    int getCodigoError() const { return codigoError; }
};

// Emisor: convierte el nodo en TramaSensor y la manda con sendto (sin conexion)
void enviarTelemetriaUDP(const NodoRedInteligente& nodo);

// Receptor: hace bind al puerto y recibe 'cantidad' tramas con recvfrom.
// Si pasan 3 segundos sin que llegue nada, lanza ExcepcionRedUDP por timeout.
void recibirTelemetriaUDP(int cantidad);

#endif