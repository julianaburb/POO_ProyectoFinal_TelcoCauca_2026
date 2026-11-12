#include "SupervisorRed.h"
#include <iostream>
#include <stdexcept>
#include "ExcepcionNodoRed.h"
#include "Registro.h"

void SupervisorRed::supervisar(DispositivoComunicacion* dev, int& transmisionesExitosas) {
    try {
        if (dev == nullptr) {
            throw std::invalid_argument("Puntero nulo detectado en el contenedor polimórfico.");
        }

        if (dev->getIp().empty() || dev->getIp() == "0.0.0.0") {
            throw ExcepcionNodoRed("Falla de IP: Dirección IP vacía o no configurada en el dispositivo.");
        }

        {
            std::lock_guard<std::mutex> lock(mtx_consola); // consola
            dev->transmitir(); // llama al transmitir() de la clase hija
            std::cout << "[TRAMA SERIALIZADA]: " << dev->serializar() << std::endl;
        }
        {
            std::lock_guard<std::mutex> lock(mtx_contador); // contador compartido
            transmisionesExitosas++;
        }
    }
    // del mas especifico al mas general
    catch (const ExcepcionNodoRed& e) {
        std::lock_guard<std::mutex> lock(mtx_consola);
        std::cerr << "[EXCEPCION NODO RED CAPTURADA EN HILO]: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::lock_guard<std::mutex> lock(mtx_consola);
        std::cerr << "[INVALID ARGUMENT CAPTURADO EN HILO]: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(mtx_consola);
        std::cerr << "[EXCEPCION GENERICA EN HILO]: " << e.what() << std::endl;
    }
}
