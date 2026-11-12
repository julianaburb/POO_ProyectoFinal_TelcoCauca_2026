#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H

#include "DispositivoComunicacion.h"

class RouterWiFi : public DispositivoComunicacion { //clase que hereda de clase DispositivoComunicacion
public:
    explicit RouterWiFi(const std::string& iP);
    ~RouterWiFi() override = default;

    void transmitir() override; 
    std::string serializar() const override;
};

#endif 