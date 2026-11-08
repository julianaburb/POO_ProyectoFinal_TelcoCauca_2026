#ifndef TORRE_H
#define TORRE_H

#include <string>
#include <vector>


class Antena;

class Torre {
private:
    int idTorre;
    std::string ubicacion;
    double alturaMetros;
    std::vector<Antena*> listaAntenas; // Asociación 1:N

public:
    Torre(int _id, const std::string& _ubic, double _alt);
    void agregarAntena(Antena* a);
    void mostrarReporteTorre() const;
    int contarAntenas5G() const;
    ~Torre();
};

#endif
