#include "Tecnico.h"

Tecnico::Tecnico(int _id, std::string _nombre, std::string _esp, bool enTurno)
    : id(_id), nombre(_nombre), especialidad(_esp), enTurno(enTurno) {}

void Tecnico::mostrarInformacion() const {
    std::cout << " [Técnico ID: " << id << "] " << nombre << " | Especialidad: " << especialidad << std::endl;
}