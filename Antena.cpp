#include "Antena.h"
#include "Tecnico.h"

Antena::Antena(int _id, double _freq, const std::string& _tec)
    : idAntena(_id), frecuenciaMHz(_freq), tecnologia(_tec), responsableMantenimiento(nullptr) {}

void Antena::asignarResponsable(Tecnico* t) {
    if (t != nullptr) {
    responsableMantenimiento = t;
    }
}

void Antena::mostrarDetalles() const {
    std::cout << " * Antena #" << idAntena << " (" << tecnologia << ", "
              << frecuenciaMHz << " MHz)";
    if (responsableMantenimiento != nullptr) {
        std::cout << " -> Resp: " << responsableMantenimiento->getNombre();
    } else {
        std::cout << " -> Resp: [SIN ASIGNAR]";
    }
    std::cout << std::endl;
}

std::string Antena::getTecnologia() const{
    return tecnologia;
}

Antena::~Antena() {}
