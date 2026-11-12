#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"


class DispositivoComunicacion : public ITransmisible {
protected:
    std::string iP;
public:
    explicit DispositivoComunicacion(const std::string& iP); // explicit: no deja convertir un string en dispositivo sin querer
    virtual ~DispositivoComunicacion() = default; //El destructor virtual
    virtual void transmitir() = 0; //lo implementan RouterWiFi, GatewayLoRa y SwitchFibra
    std::string getIp() const;
};

#endif
