#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H
#include <string>

class ITransmisible { //interfaz pura
public:
    //Metodo virtual puro que obliga a las hijas a implementar la serializacion
    //es const porque solo puede leer los atributos del objeto, no cambiarlos,
    // enviar un dispositivo por la red no debería cambiarlo
    virtual std::string serializar () const = 0;

    //Destructor virtual para que delete desde un ITransmisible*
    // llame tambien al destructor de la clase hija
    virtual ~ITransmisible() = default; 
};

#endif