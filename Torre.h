#ifndef TORRE_H
#define TORRE_H

#include <string>
#include <vector>
#include <iostream>
#include "Antena.h"

class Torre {
private:
    std::string idTorre;
    std::string ubicacion;
    double alturaMetros;
    std::vector<Antena*> listaAntenas; // Asociación 1:N

public:
    Torre(std::string _id, std::string _ubic, double _alt);
    void agregarAntena(Antena* a);
    void mostrarReporteTorre() const;
    int contarAntenas5G() const;
};

#endif
