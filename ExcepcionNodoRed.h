#ifndef EXCEPCION_NODO
#define EXCEPCION_NODO
#include <iostream>
#include <exception>
#include <string>

class ExcepcionNodoRed: public std::runtime_error{
public:
    ExcepcionNodoRed (const std::string& mensaje) : std::runtime_error(mensaje) {}
};

#endif
