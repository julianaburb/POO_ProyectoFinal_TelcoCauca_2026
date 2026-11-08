#ifndef TECNICO_H
#define TECNICO_H
#include <string>
#include <iostream>
class Tecnico {
private:
int idTecnico;
std::string nombre;
std::string especialidad;

public:
Tecnico(int _id, const std::string &_nombre, const std::string &_esp);
void mostrarInformacion() const;
int getIdTecnico() const {return idTecnico;}
std::string getNombre() const { return nombre;}
std::string getEspecialidad ()const {return especialidad;}
void setIdTecnico (int nuevoIdTecnico);
void setNombre (const std::string &nuevoNombre);
void setEspecialidad (const std::string &nuevaEspecialidad);

};
#endif