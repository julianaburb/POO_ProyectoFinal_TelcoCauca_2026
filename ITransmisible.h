#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H
#include <string>

class ITransmisible { //interfaz pura
public:
    // las hijas tienen que implementarlo. Es const porque serializar no cambia el objeto
    virtual std::string serializar () const = 0;

    // virtual para que delete desde un ITransmisible* llame tambien al destructor de la hija
    virtual ~ITransmisible() = default;
};

#endif
