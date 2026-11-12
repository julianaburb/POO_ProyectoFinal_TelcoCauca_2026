#include "NodoRedInteligente.h"
#include <stdexcept>
#include "ExcepcionNodoRed.h"

NodoRedInteligente::NodoRedInteligente(const std::string& direccionIp, const std::string& direccionMAC, bool estadoOperativo,
                                       const std::string& tipoSensor, double valorLectura, int idNodo,
                                       int paquetesProcesados, double cargaProcesamiento)
    : DispositivoRed(direccionIp, direccionMAC, estadoOperativo), SensorIot(tipoSensor, valorLectura) {
    this->idNodo = idNodo;
    this->paquetesProcesados = paquetesProcesados;
    this->cargaProcesamiento = cargaProcesamiento;
}

NodoRedInteligente NodoRedInteligente::operator+(const NodoRedInteligente& otro) const {
    NodoRedInteligente resultado(*this);
    resultado.cargaProcesamiento = cargaProcesamiento + otro.cargaProcesamiento;
    return resultado;
} //this siempre sera el de la izquierda y el q es paso por referencia siempre sera el de la derecha

// no lleva NodoRedInteligente:: porque es funcion amiga, no metodo
std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n) {
    os << "----- Nodo de Red Inteligente -----" << std::endl;
    os << "ID del nodo:          " << n.idNodo << std::endl;
    os << "Direccion IP:         " << n.direccionIP << std::endl;
    os << "Direccion MAC:        " << n.direccionMAC << std::endl;
    os << "Estado operativo:     " << (n.estadoOperativo ? "Activo" : "Inactivo") << std::endl;
    os << "Tipo de sensor:       " << n.tipoSensor << std::endl;
    os << "Valor de lectura:     " << n.valorLectura << std::endl;
    os << "Paquetes procesados:  " << n.paquetesProcesados << std::endl;
    os << "Carga procesamiento:  " << n.cargaProcesamiento << std::endl;
    return os; // se devuelve os para poder hacer cout << n1 << n2
}

// trama con el formato TIPO|ID|IP|VALOR
std::string NodoRedInteligente::serializar() const {
    return "SENSOR|" + std::to_string(idNodo) + "|" + direccionIP + "|" + std::to_string(valorLectura);
}
