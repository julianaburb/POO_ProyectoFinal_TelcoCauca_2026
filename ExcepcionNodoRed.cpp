#include "ExcepcionNodoRed.h"

// Pasa el mensaje formateado al constructor base de std::runtime_error
ExcepcionNodoRed::ExcepcionNodoRed(const std::string& mensaje)
    : std::runtime_error("[Excepción Nodo Red]: " + mensaje) {
};