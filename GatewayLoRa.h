#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H

#include "DispositivoComunicacion.h"

class GatewayLoRa : public DispositivoComunicacion {
public:
    explicit GatewayLoRa(const std::string& iP);
    ~GatewayLoRa() override = default;

    void transmitir() override;
    std::string serializar() const override;
};

#endif 