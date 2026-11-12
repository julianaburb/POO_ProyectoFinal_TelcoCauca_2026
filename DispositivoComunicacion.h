#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"


class DispositivoComunicacion : public ITransmisible {
protected:
    std::string iP;
public:
    explicit DispositivoComunicacion(const std::string& iP); //En el constructor, "explicit" evita conversiones implícitas automáticas
    virtual ~DispositivoComunicacion() = default; //El destructor virtual 
    virtual void transmitir() = 0; //El método que heredan las clases RouterWiFi.h, GatewatLoRa.h y SwichFibra.h
    std::string getIp() const;
};

#endif
