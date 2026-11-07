#ifndef SENSORIOT_H
#define SENSORIOT_HSensorIot
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

class SensorIot{
protected:
    string tipoSensor;
    double valorLectura;
public:
    SensorIot(string tipoSensor, double valorLectura);
    
    void mostrarValorLectura () {
        if (this->valorLectura < -50.0 || this->valorLectura > 100.0) {
            throw std::out_of_range ("ERROR: se ha ingresado un valor fuera del rango");
        }
        cout << "El valor de la laectura es: "<< valorLectura << endl;
    } 
};
#endif