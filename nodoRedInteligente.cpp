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

// Sobrecarga del operador << para mostrar el nodo en consola de forma ordenada.
// Va sin NodoRedInteligente:: adelante porque no es un metodo de la clase,
// es una funcion amiga. Por ser amiga puede leer los atributos protegidos
// que el nodo hereda de DispositivoRed y SensorIot, y tambien los privados
std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n) {
    os << "----- Nodo de Red Inteligente -----" << std::endl;
    os << "ID del nodo:          " << n.idNodo << std::endl;
    os << "Direccion IP:         " << n.direccionIP << std::endl;
    os << "Direccion MAC:        " << n.direccionMAC << std::endl;
    os << "Estado operativo:     " << (n.estadoOperativo ? "Activo" : "Inactivo") << std::endl;
    os << "Tipo de sensor:       " << n.tipoSensor << std::endl;
    os << "Valor de lectura:     " << n.valorLectura << std::endl;
    os << "Carga procesamiento:  " << n.cargaProcesamiento << std::endl;
    // Devolvemos el mismo flujo para poder encadenar, por ejemplo: cout << n1 << n2;
    return os;
}