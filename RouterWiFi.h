// MODULO 3.2 - SUBCLASE CONCRETA: RouterWiFi
#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H

#include "DispositivoComunicacion.h"

class RouterWiFi : public DispositivoComunicacion {
private:
    int canalesActivos;
public:
    RouterWiFi(const std::string& _id, int _canales);

    // override hace que el compilador revise que la firma sea igual a la de la base
    void transmitir() override;
};

#endif
