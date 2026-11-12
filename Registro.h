// MODULO 4 - EXCLUSION MUTUA (std::mutex + std::lock_guard)
#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <mutex>

// extern: los mutex se crean una sola vez en Registro.cpp y los demas archivos los usan
extern std::mutex mtx_consola;   // para todo lo que se imprime desde varios hilos
extern std::mutex mtx_contador;  // para el contador de transmisiones exitosas

void registrarEventoSeguro(const std::string& mensaje);

#endif
