#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"

using namespace std;

class DispositivoComunicacion : public ITransmisible {
protected:
    string iP;
public:
    explicit DispositivoComunicacion(const string& iP);
    virtual ~DispositivoComunicacion() = default; //el destructor
    virtual void transmitir() = 0; // el mtd qque debo heredar para routerwifi, gateway y swichfibra
    std::string getIp() const;
};

#endif
