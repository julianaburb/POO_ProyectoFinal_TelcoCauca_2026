#include "sensorIot.h"
#include "ExcepcionNodoRed.h"
#include <string>

SensorIot::SensorIot(const std::string& tipoSensor, double valorLectura)
    : tipoSensor(tipoSensor), valorLectura(0) {
    setValorLectura(valorLectura);   // el constructor usa el setter
}

void SensorIot::setValorLectura(double v) {
    if (v < -50 || v > 100)
        throw ExcepcionNodoRed("Lectura fuera de rango: " + std::to_string(v));
    valorLectura = v;
}