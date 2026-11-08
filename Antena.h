#ifndef ANTENA_H
#define ANTENA_H

#include <string>
#include <iostream>
#include "Tecnico.h"

class Antena {
private:
    int idAntena;
    double frecuenciaMHz;
    std::string tecnologia; // ej: "4G", "5G"
    Tecnico* responsable;   // Asociación 1:1 con Técnico

public:
    Antena(int _id, double _freq, std::string _tec);
    void asignarTecnico(Tecnico* t);
    void mostrarDetalles() const;
    std::string getTecnologia() const;
    void reemplazarTecnico(Tecnico* antiguo, Tecnico* nuevo);
};

#endif