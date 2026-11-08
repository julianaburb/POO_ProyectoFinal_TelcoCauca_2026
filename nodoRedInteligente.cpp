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
//NodoRedInteligente NodoRedInteligente:: operator+(const NodoRedInteligente& nodo) const {
  //      if(this->direccionIp != nodo.direccionIp) {
    //            throw ExcepcionNodoRed("DIRECCIONES IP NO COMPATIBLES");
      //  }
        //int totalPaquetes= this->paquetesProcesados + nodo.paquetesProcesados;
        //double promedio= totalPaquetes/2;
      //  int combinarIdentificadores = (this->idNodo *100) + nodo.idNodo;
      //  return NodoRedInteligente(this->direccionIp, this->anchoBandaMbps, this->tipoSensor, promedio, combinarIdentificadores, totalPaquetes);
// }
    //this siempre sera el de la izquierda y el q es paso por referencia siempre sera el de la derecha