#include "DispositivoComunicacion.h"

DispositivoComunicacion::DispositivoComunicacion(const std::string& _id, const std::string& _tipo)
    : id(_id), tipo(_tipo) {}

// el destructor ya quedo como = default en el .h, por eso no va aca

std::string DispositivoComunicacion::getId() const { return id; }
std::string DispositivoComunicacion::getTipo() const { return tipo; }
