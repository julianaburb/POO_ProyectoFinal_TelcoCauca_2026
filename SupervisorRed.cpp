#include "SupervisorRed.h"
#include <iostream>
#include <stdexcept>
#include "ExcepcionNodoRed.h"

void SupervisorRed::supervisar(DispositivoComunicacion* dev, int& transmisionesExitosas) {
    try {
        // Guarda 1: Puntero nulo
        if (dev == nullptr) {
            throw std::invalid_argument("Puntero nulo detectado en el contenedor polimórfico.");
        }

        // Guarda 2: IP inválida o vacía (Lanza ExcepcionNodoRed)
        if (dev->getIp().empty() || dev->getIp() == "0.0.0.0") {
            throw ExcepcionNodoRed("Falla de IP: Dirección IP vacía o no configurada en el dispositivo.");
        }

        // Ejecución de la transmisión polimórfica
        dev->transmitir();

        // Secciones críticas protegidas por RAII (std::lock_guard)
        {
            std::lock_guard<std::mutex> lock(mtxConsola);
            std::cout << "[TRAMA SERIALIZADA]: " << dev->serializar() << std::endl;
            transmisionesExitosas++;
        }
    }
    // Captura en orden jerárquico: de lo específico a lo general
    catch (const ExcepcionNodoRed& e) {
        std::lock_guard<std::mutex> lock(mtxConsola);
        std::cerr << "[EXCEPCION NODO RED CAPTURADA EN HILO]: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::lock_guard<std::mutex> lock(mtxConsola);
        std::cerr << "[INVALID ARGUMENT CAPTURADO EN HILO]: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(mtxConsola);
        std::cerr << "[EXCEPCION GENERICA EN HILO]: " << e.what() << std::endl;
    }
}