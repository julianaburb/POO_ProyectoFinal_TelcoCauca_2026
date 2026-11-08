#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H

#include "DispositivoComunicacion.h"

class SwitchFibra : public DispositivoComunicacion {
public:
    explicit SwitchFibra(const std::string& iP);
    ~SwitchFibra() override = default;

    void transmitir() override;
    std::string serializar() const override;
};

#endif 
