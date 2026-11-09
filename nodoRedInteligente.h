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
    NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
    friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n) {
        os << "ID del nodo es: " << n.idNodo <<endl;
        return os;
    }    
};
#endif

