#include "EventoIngenieria2027.h"
#include "Registro.h"
#include <thread>
#include <chrono>
#include <stdexcept>

EventoIngenieria2027::EventoIngenieria2027(const std::string& _nombre, const std::string& _fecha,
                                           const std::string& _lugar, const std::string& _enfoque, int _anio)
    : nombre(_nombre), fecha(_fecha), lugar(_lugar), enfoque(_enfoque), anio(_anio) {}

void EventoIngenieria2027::validarAnio() const {
    if (anio != 2027) {
        throw std::out_of_range("El evento " + nombre + " no esta proyectado para 2027.");
    }
}

std::string EventoIngenieria2027::getNombre() const { return nombre; }
int EventoIngenieria2027::getAnio() const { return anio; }

std::string EventoIngenieria2027::resumen() const {
    // lo armo en un solo string para que salga completo en un solo bloqueo del mutex
    return "EVENTO 2027 -> " + nombre +
           "\n      Fecha  : " + fecha +
           "\n      Lugar  : " + lugar +
           "\n      Enfoque: " + enfoque;
}

void procesarAgendaEventos2027(const std::vector<EventoIngenieria2027*>& agenda, int& eventosMostrados) {
    try {
        if (agenda.empty()) {
            throw std::runtime_error("La agenda de eventos 2027 esta vacia.");
        }

        registrarEventoSeguro("===== AGENDA DE EVENTOS DE INGENIERIA 2027 =====");

        for (std::size_t i = 0; i < agenda.size(); ++i) {
            // try-catch por cada evento: si uno falla, los demas se siguen mostrando
            try {
                // Guarda defensiva, igual que con los dispositivos
                if (agenda[i] == nullptr) {
                    throw std::invalid_argument("ERROR: Evento nulo en la agenda 2027.");
                }
                agenda[i]->validarAnio();

                registrarEventoSeguro(agenda[i]->resumen());   // salida protegida por mutex
                ++eventosMostrados;   // solo este hilo la toca, main la lee despues del join
            }
            catch (const std::invalid_argument& e) {
                registrarEventoSeguro(std::string("[Argumento Invalido] EXCEPCION EN HILO DE EVENTOS: ") + e.what());
            }
            catch (const std::out_of_range& e) {
                registrarEventoSeguro(std::string("[Fuera de Rango] EXCEPCION EN HILO DE EVENTOS: ") + e.what());
            }

            // pausa breve para que se note que corre a la par con los otros hilos
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    catch (const std::exception& e) {
        registrarEventoSeguro(std::string("EXCEPCION EN HILO DE EVENTOS: ") + e.what());
    }
}
