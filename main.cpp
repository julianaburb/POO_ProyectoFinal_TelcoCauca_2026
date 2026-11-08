// MODULO 3.5 - ORQUESTACION, SINCRONIZACION Y MEMORIA
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <functional>   // std::ref

#include "DispositivoComunicacion.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "TareaTransmision.h"
#include "EventoIngenieria2027.h"
#include "Registro.h"

int main() {
    // 1. Vector heterogeneo de dispositivos en el Heap
    // se guardan punteros y no objetos para que no haya slicing
    std::vector<DispositivoComunicacion*> red;
    red.push_back(new RouterWiFi("RTR-01", 12));
    red.push_back(new GatewayLoRa("GW-868", 868.1f));
    red.push_back(new SwitchFibra("SW-FO-01", 10));
    red.push_back(nullptr); // Provocacion intencional para probar la guarda defensiva

    // Variable compartida entre hilos (protegida con mtx_contador)
    int transmisionesExitosas = 0;

    // Agenda de eventos 2027 (Modulo 4), tambien en el Heap
    std::vector<EventoIngenieria2027*> agenda;
    agenda.push_back(new EventoIngenieria2027(
        "NVIDIA GTC 2027",
        "15 al 18 de marzo de 2027",
        "San Jose, California (EE.UU.) - San Jose McEnery Convention Center",
        "IA y computacion acelerada: infraestructura de IA, IA agentica, CUDA, IA fisica y robotica",
        2027));
    agenda.push_back(new EventoIngenieria2027(
        "ITW Global 2027 (International Telecoms Week)",
        "10 al 13 de mayo de 2027",
        "National Harbor, Maryland (EE.UU.) - Gaylord National Resort & Convention Center",
        "Conectividad e infraestructura digital: operadores, data centers, nube y redes para la era de la IA",
        2027));
    agenda.push_back(new EventoIngenieria2027(
        "Telco Transformation LATAM 2027 (Conecta Latam)",
        "Agosto de 2027 (proyectado, fecha oficial por confirmar)",
        "Rio de Janeiro, Brasil (sede de las ediciones 2025 y 2026)",
        "Transformacion de operadores: IA, OpenRAN, automatizacion de redes, IoT, nube y ciberseguridad",
        2027));

    int eventosMostrados = 0;

    // 2. Vector de hilos independientes (paso por referencia con std::ref)
    // sin std::ref el hilo trabaja con una copia y el contador del main se queda en 0
    std::vector<std::thread> hilos;
    for (DispositivoComunicacion* dev : red) {
        hilos.push_back(std::thread(tareaTransmisionHilo, dev, std::ref(transmisionesExitosas)));
    }

    // Hilo dedicado a la agenda de eventos 2027
    hilos.push_back(std::thread(procesarAgendaEventos2027, std::ref(agenda), std::ref(eventosMostrados)));

    // 3. Sincronizacion obligatoria de hilos
    // si un hilo queda joinable cuando se destruye, el programa se cae con terminate()
    for (auto& t : hilos) {
        if (t.joinable()) {
            t.join();
        }
    }

    registrarEventoSeguro("Transmisiones exitosas: " + std::to_string(transmisionesExitosas)
                          + " de " + std::to_string(red.size()) + " dispositivos");
    registrarEventoSeguro("Eventos 2027 registrados: " + std::to_string(eventosMostrados));

    // 4. Liberacion limpia de memoria dinamica
    // ya todos los hilos terminaron, entonces aca si se puede borrar sin problema
    for (std::size_t i = 0; i < red.size(); ++i) {
        if (red[i] != nullptr) {
            delete red[i];
        }
        red[i] = nullptr;   // para no dejar punteros colgantes
    }
    red.clear();

    for (std::size_t i = 0; i < agenda.size(); ++i) {
        if (agenda[i] != nullptr) {
            delete agenda[i];
        }
        agenda[i] = nullptr;
    }
    agenda.clear();

    // aca ya solo queda el hilo principal, por eso el cout va sin mutex
    std::cout << "Sistema finalizado correctamente." << std::endl;
    return 0;
    
}
