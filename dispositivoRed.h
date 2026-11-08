#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H
using namespace std;
#include <iostream>
#include <string>
#include <stdexcept>

class DispositivoRed{
protected:
    string direccionIp;
    std::string direccionMAC;
    bool estadoOperativo;
public:
    DispositivoRed (std::string direccionIp, std::string direccionMAC, bool estadoOperativo);
    
    void LecturaIp() {  
        if (this->direccionIp.empty()) {
            throw std::invalid_argument ("Puntero a Ip vacio"); 
    } 
    std::cout << "La ip es: " << direccionIp <<endl; 
}
} ;

#endif