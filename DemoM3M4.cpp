#include "DemoM3M4.h"

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>

// Inclusión de los encabezados del contrato del Proyecto Integrador
#include "DispositivoComunicacion.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "SupervisorRed.h"
#include "EventoIngenieria2027.h"
#include "ExcepcionNodoRed.h"

// Opción 3 del Menú: Demostración de Polimorfismo, Guardas y Supervisión Multihilo
void demoSupervisionHilos() {
    std::cout << "\n=========================================================\n";
    std::cout << "  DEMO OPCION 3: SUPERVISION MULTIHILO Y POLIMORFISMO   \n";
    std::cout << "=========================================================\n\n";

    // 1. Creación del contenedor heterogéneo polimórfico en el Heap (Módulo 3)
    std::vector<DispositivoComunicacion*> red;
    red.push_back(new RouterWiFi("192.168.1.1"));
    red.push_back(new GatewayLoRa("10.0.0.50"));
    red.push_back(new SwitchFibra("172.16.0.100"));
    
    // Provocaciones intencionales para evaluación defensiva (Sección 2.3 y 2.4)
    red.push_back(nullptr);                  // Provoca std::invalid_argument (Puntero nulo)
    red.push_back(new RouterWiFi(""));        // Provoca ExcepcionNodoRed (IP vacía/inválida)

    // 2. Objeto supervisor y variables para hilos concurrentes
    SupervisorRed supervisor;
    int transmisionesExitosas = 0;
    std::vector<std::thread> hilos;

    std::cout << "--- Ejecutando hilos de supervisión sobre vector polimórfico ---\n";

    // 3. Creación de un hilo por dispositivo llamando a la función miembro de SupervisorRed (Módulo 4)
    for (DispositivoComunicacion* dev : red) {
        hilos.push_back(
            std::thread(&SupervisorRed::supervisar, &supervisor, dev, std::ref(transmisionesExitosas))
        );
    }

    // 4. Sincronización obligatoria (.join()) de todos los hilos (Sección 2.4)
    for (auto& t : hilos) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\nResumen: Transmisiones procesadas exitosamente: " 
              << transmisionesExitosas << " de " << red.size() << " elementos.\n";

    // 5. Liberación limpia de memoria en el Heap sin fugas (Destructores Virtuales)
    std::cout << "\n--- Liberando memoria dinamica del Heap ---\n";
    for (size_t i = 0; i < red.size(); ++i) {
        if (red[i] != nullptr) {
            delete red[i];
            red[i] = nullptr;
        }
    }
    red.clear();
    std::cout << "[OK] Memoria liberada correctamente.\n";
}

// Opción 4 del Menú: Demostración de Agenda Concurrente de Eventos 2027
void demoEventos2027() {
    std::cout << "\n=========================================================\n";
    std::cout << "  DEMO OPCION 4: AGENDA CONCURRENTE DE EVENTOS 2027     \n";
    std::cout << "=========================================================\n\n";

    std::mutex mtxConsolaLocal;

    // Ejecución en hilo dedicado e independiente de procesarEventos2027 (Sección 2.4)
    std::thread hiloEventos(procesarEventos2027, std::ref(mtxConsolaLocal));

    // Sincronización obligatoria del hilo
    if (hiloEventos.joinable()) {
        hiloEventos.join();
    }

    std::cout << "[OK] Hilo de eventos 2027 finalizado correctamente.\n";
}