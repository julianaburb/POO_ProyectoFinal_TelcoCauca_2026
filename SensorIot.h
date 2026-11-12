#ifndef SENSORIOT_H
#define SENSORIOT_H

#include <string>
#include <iostream>
#include <stdexcept>

class SensorIot{

protected:
    std::string tipoSensor;
    double valorLectura;
public:
    SensorIot(const std::string& tipoSensor, double valorLectura);
    void setValorLectura(double v);
    double getValorLectura() const { return valorLectura; }
        std::string getTipoSensor() const { return tipoSensor; }
};

#endif