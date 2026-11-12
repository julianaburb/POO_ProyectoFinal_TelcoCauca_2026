#include "Tecnico.h"
#include <string>

using namespace std;

Tecnico::Tecnico (int _idTecnico, const std::string &_nombre, const std::string &_esp)
    : idTecnico(_idTecnico), nombre(_nombre), especialidad(_esp) {}

void Tecnico::mostrarInformacion() const {
    std::cout << " [Técnico ID: " << idTecnico << "] " << nombre << " | Especialidad: " << especialidad << std::endl;
}

void Tecnico::setIdTecnico (int nuevoIdTecnico){
    this->idTecnico = nuevoIdTecnico;
}

void Tecnico::setNombre (const std::string &nuevoNombre){
    this->nombre = nuevoNombre;
}

void Tecnico::setEspecialidad (const std::string &nuevaEspecialidad){
    this->especialidad = nuevaEspecialidad;
}