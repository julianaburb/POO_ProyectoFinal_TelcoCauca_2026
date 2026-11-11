#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H
#include <iostream>
#include <string>
#include <stdexcept>

class DispositivoRed{
protected:
    std::string direccionIP;
    std::string direccionMAC;
    bool estadoOperativo;
public:
    DispositivoRed(const std::string& direccionIP, const std::string& direccionMAC, bool estadoOperativo);
    std::string getDireccionIP() const { return direccionIP; }
    void validarIP() const;
} ;

#endif

