#ifndef EXCEPCIONNODORED_H
#define EXCEPCIONNODORED_H

#include <stdexcept>
#include <string>

class ExcepcionNodoRed : public std::runtime_error {
    public:
    // explicit: evita que un std::string se convierta implícitamente en una
    // ExcepcionNodoRed; la excepción solo se crea de forma intencional
        explicit ExcepcionNodoRed(const std::string& mensaje);
};

#endif
