// MODULO 3.1 - CLASE BASE ABSTRACTA (CONTRATO POLIMORFICO)
#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>

class DispositivoComunicacion {
protected:
    std::string id;
    std::string tipo;
public:
    DispositivoComunicacion(const std::string& _id, const std::string& _tipo);

    // Destructor virtual: indispensable para liberacion polimorfica en el Heap
    // sin esto el delete desde el puntero base solo borra la parte de la base
    virtual ~DispositivoComunicacion() = default;

    // Metodo virtual puro: define la interfaz obligatoria
    // por esto la clase queda abstracta y no se puede hacer new DispositivoComunicacion
    virtual void transmitir() = 0;

    std::string getId() const;
    std::string getTipo() const;
};

#endif
