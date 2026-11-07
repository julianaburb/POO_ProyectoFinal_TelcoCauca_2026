#ifndef NODOREDINTELIGENTE_H 
#define NODOREDINTELIGENTE_H 
using namespace std;
#include "dispositivoRed.h"
#include "sensorIot.h"


class NodoRedInteligente: public DispositivoRed, public SensorIot {
private:
    int idNodo;
    int paquetesProcesados;
public:
    NodoRedInteligente (string direccionIp, double anchoBandaMbps, string tipoSensor, double valorLectura, int idNodo, int paquetesProcesados);
    NodoRedInteligente operator+(const NodoRedInteligente& nodo) const;
    friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n) {
        os << "ID del nodo es: " << n.idNodo <<endl;
        return os;
    }
};
#endif

