#ifndef NODOREDINTELIGENTE_H 
#define NODOREDINTELIGENTE_H 
#include "dispositivoRed.h"
#include "sensorIot.h"


class NodoRedInteligente: public DispositivoRed, public SensorIot {
private:
    int idNodo;
    int paquetesProcesados;
    double cargaProcesamiento;
public:
    NodoRedInteligente (std::string direccionIp, std::string direccionMAC, bool estadoOperativo, string tipoSensor, double valorLectura, int idNodo, int paquetesProcesados, double cargaProcesamiento);
    int getIdNodo() const { return idNodo; }
    NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
    // Lo declaro como friend porque a la izquierda del << va std::cout y no el nodo,
    // entonces no puede ser un metodo de la clase, pero igual necesita leer los atributos.
    friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n);
        // Convierte el nodo en un texto para poder mandarlo por la red
    std::string serializar() const;

};
#endif

