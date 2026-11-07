// MODULO 4 - REGISTRO DE EVENTOS DE INGENIERIA 2027
#ifndef EVENTOINGENIERIA2027_H
#define EVENTOINGENIERIA2027_H

#include <string>
#include <vector>

class EventoIngenieria2027 {
private:
    std::string nombre;
    std::string fecha;
    std::string lugar;
    std::string enfoque;   // de que trata el evento
    int anio;
public:
    EventoIngenieria2027(const std::string& _nombre, const std::string& _fecha,
                         const std::string& _lugar, const std::string& _enfoque, int _anio);

    // revisa que el evento si sea del 2027, si no lanza excepcion
    void validarAnio() const;

    std::string getNombre() const;
    int getAnio() const;
    std::string resumen() const;
};

// Funcion que corre en un hilo aparte: recorre la agenda y la muestra con el mutex.
// La agenda y el contador llegan por referencia, en el main se pasan con std::ref
void procesarAgendaEventos2027(const std::vector<EventoIngenieria2027*>& agenda, int& eventosMostrados);

#endif
