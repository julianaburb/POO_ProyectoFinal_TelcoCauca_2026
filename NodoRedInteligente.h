#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H
#include <string>
#include <iostream>
#include "DispositivoRed.h"
#include "SensorIot.h"


class NodoRedInteligente: public DispositivoRed, public SensorIot {
private:
    int idNodo;
    int paquetesProcesados;
    double cargaProcesamiento;
public:
    NodoRedInteligente(const std::string& direccionIp, const std::string& direccionMAC, bool estadoOperativo,
                       const std::string& tipoSensor, double valorLectura, int idNodo,
                       int paquetesProcesados, double cargaProcesamiento);
    int getIdNodo() const { return idNodo; }
    int getPaquetesProcesados() const { return paquetesProcesados; }
    NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
    // friend porque a la izquierda del << va el cout y no el nodo
    friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n);
    // pasa el nodo a texto para mandarlo por TCP
    std::string serializar() const;

};
#endif
