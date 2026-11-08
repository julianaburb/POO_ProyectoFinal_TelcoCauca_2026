#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H

#include "DispositivoComunicacion.h"

class RouterWiFi : public DispositivoComunicacion {
public:
    explicit RouterWiFi(const std::string& iP);
    ~RouterWiFi() override = default;

    void transmitir() override;
    std::string serializar() const override;
};

#endif 