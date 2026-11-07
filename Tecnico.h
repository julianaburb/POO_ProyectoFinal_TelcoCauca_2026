#ifndef TECNICO_H
#define TECNICO_H
#include <string>
#include <iostream>
class Tecnico {
private:
int id;
std::string nombre;
std::string especialidad;
bool enTurno;

public:
Tecnico(int _id, std::string _nombre, std::string _esp, bool enTurno);
void mostrarInformacion() const;
std::string getNombre() const { return nombre; }
bool getEnTurno () const {return enTurno; }
};
#endif