#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H

using namespace std;

#include <iostream>
#include <string>
#include <stdexcept>

class DispositivoRed{
protected:
    std::string direccionIP;
    std::string direccionMAC;
    bool estadoOperativo;
public:
    DispositivoRed (std::string direccionIP, std::string direccionMAC, bool estadoOperativo);
    string getDireccionIP() const;

    void LecturaIp() {  
        if (this->direccionIP.empty()) {
            throw std::invalid_argument ("Puntero a Ip vacio"); 
    } std::cout << "La ip es: " << direccionIP <<endl; 
    }
} ;

#endif