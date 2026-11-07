// MODULO 3.3 - EXCLUSION MUTUA (std::mutex + std::lock_guard, patron RAII)
#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <mutex>

// extern porque los mutex se crean una sola vez en Registro.cpp y los demas archivos los usan
extern std::mutex mtx_consola;   // Protege la salida estandar compartida
extern std::mutex mtx_contador;  // Protege variables compartidas (contador de exitosas)

void registrarEventoSeguro(const std::string& mensaje);

#endif
