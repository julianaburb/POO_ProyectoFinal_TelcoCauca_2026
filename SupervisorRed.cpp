#include "SupervisorRed.h"
#include <iostream>
#include <stdexcept>
#include "ExcepcionNodoRed.h"
#include "Registro.h"   // mtx_consola: el mismo mutex de consola que usa el resto del programa

void SupervisorRed::supervisar(DispositivoComunicacion* dev, int& transmisionesExitosas) {
    try {
        if (dev == nullptr) {
            throw std::invalid_argument("Puntero nulo detectado en el contenedor polimórfico.");
        } //el Puntero nulo

        if (dev->getIp().empty() || dev->getIp() == "0.0.0.0") {
            throw ExcepcionNodoRed("Falla de IP: Dirección IP vacía o no configurada en el dispositivo.");
        } //IP inválida o vacía (Lanza ExcepcionNodoRed)

        {
            std::lock_guard<std::mutex> lock(mtx_consola);
            dev->transmitir(); //la vaina esa polimorfica
            std::cout << "[TRAMA SERIALIZADA]: " << dev->serializar() << std::endl;
            transmisionesExitosas++;
        }  // Secciones críticas protegidas por RAII 
    }
    // las capturas orden jerárquico, espf a gen
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