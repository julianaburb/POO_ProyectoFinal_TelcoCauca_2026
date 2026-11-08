#include "ExcepcionNodoRed.h"

ExcepcionNodoRed::ExcepcionNodoRed(const std::string& mensaje)
    : std::runtime_error(mensaje) {
};