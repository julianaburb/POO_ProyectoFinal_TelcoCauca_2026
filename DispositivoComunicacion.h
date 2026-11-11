#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"

using namespace std;

class DispositivoComunicacion : public ITransmisible {
protected:
    string iP;
public:
    explicit DispositivoComunicacion(const string& iP); //No sé qué hace
    virtual ~DispositivoComunicacion() = default; //el destructor
    virtual void transmitir() = 0; // el método que debo heredar para RouterWiFi, gateway y swichfibra
    std::string getIp() const;
};

#endif
