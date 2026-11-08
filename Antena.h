#ifndef ANTENA_H
#define ANTENA_H

#include <string>
#include <iostream>

class Tecnico; 

class Antena {
private:
    int idAntena;
    double frecuenciaMHz;
    std::string tecnologia; // ej: "4G", "5G"
    Tecnico* responsableMantenimiento;   // Asociación 1:1 con Técnico

public:
    Antena(int _id, double _freq, const std::string& _tec);
    void asignarResponsable(Tecnico* t);
    void mostrarDetalles() const;
    std::string getTecnologia() const;
    int getIdAntena() const { return idAntena; }
    double getFrecuenciaMHz() const { return frecuenciaMHz; }

    ~Antena();
};

#endif