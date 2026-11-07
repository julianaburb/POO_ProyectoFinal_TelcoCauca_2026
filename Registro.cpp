#include "Registro.h"
#include <iostream>
#include <thread>

std::mutex mtx_consola;
std::mutex mtx_contador;

void registrarEventoSeguro(const std::string& mensaje) {
    // RAII: bloquea mtx_consola al crearse y lo libera automaticamente al salir
    // sin el mutex los cout de varios hilos se mezclan en la misma linea
    std::lock_guard<std::mutex> lock(mtx_consola);
    std::cout << "[HILO " << std::this_thread::get_id() << "] "
              << mensaje << std::endl;
}
