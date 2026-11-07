#include "Antena.h"

Antena::Antena(int _id, double _freq, std::string _tec)
    : idAntena(_id), frecuenciaMHz(_freq), tecnologia(_tec), responsable(nullptr) {}

void Antena::asignarTecnico(Tecnico* t) {
    responsable = t;
}

void Antena::mostrarDetalles() const {
    std::cout << " * Antena #" << idAntena << " (" << tecnologia << ", "
              << frecuenciaMHz << " MHz)";
    if (responsable != nullptr) {
        std::cout << " -> Resp: " << responsable->getNombre();
    } else {
        std::cout << " -> Resp: [SIN ASIGNAR]";
    }
    std::cout << std::endl;
}

std::string Antena::getTecnologia() const{
    return tecnologia;
}

void Antena::reemplazarTecnico(Tecnico* antiguo, Tecnico* nuevo){
    if (antiguo != nullptr && nuevo != nullptr){
        if (responsable == antiguo && antiguo->getEnTurno() == false){
            responsable = nuevo;
         }
    }
}