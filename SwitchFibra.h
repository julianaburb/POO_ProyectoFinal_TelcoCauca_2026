// MODULO 3.2 - SUBCLASE CONCRETA: SwitchFibra
#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H

#include "DispositivoComunicacion.h"

class SwitchFibra : public DispositivoComunicacion {
private:
    int velocidadGbps;   // igual que en el caso de estudio del lab 333
public:
    SwitchFibra(const std::string& _id, int _velocidad);
    void transmitir() override;
};

#endif
