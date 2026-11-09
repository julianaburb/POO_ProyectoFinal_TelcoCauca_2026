#include "nodoRedInteligente.h"
#include <stdexcept>
#include "ExcepcionNodoRed.h"
using namespace std;

NodoRedInteligente :: NodoRedInteligente(string direccionIp, std::string direccionMAC, bool estadoOperativo, string tipoSensor,
     double valorLectura, int idNodo, int paquetesProcesados, double cargaProcesamiento): DispositivoRed(direccionIp, direccionMAC, estadoOperativo), SensorIot(tipoSensor, valorLectura) { 
        this-> idNodo = idNodo;
        this-> paquetesProcesados = paquetesProcesados;
        this-> cargaProcesamiento = cargaProcesamiento;
}
NodoRedInteligente NodoRedInteligente:: operator+(const NodoRedInteligente& otro) const {
    NodoRedInteligente resultado(*this);
    resultado.cargaProcesamiento = cargaProcesamiento + otro.cargaProcesamiento;
    return resultado;
 } //this siempre sera el de la izquierda y el q es paso por referencia siempre sera el de la derecha