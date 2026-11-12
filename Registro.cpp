#include "Registro.h"
#include <iostream>
#include <thread>

std::mutex mtx_consola;
std::mutex mtx_contador;

void registrarEventoSeguro(const std::string& mensaje) {
    // el lock_guard bloquea el mutex aca y lo suelta solo al salir de la funcion
    std::lock_guard<std::mutex> lock(mtx_consola);
    std::cout << "[HILO " << std::this_thread::get_id() << "] "
              << mensaje << std::endl;
}
