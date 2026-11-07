// MODULO 3.4 - PROGRAMACION DEFENSIVA Y EXCEPCIONES
#ifndef TAREATRANSMISION_H
#define TAREATRANSMISION_H

#include "DispositivoComunicacion.h"

// 'exitosas' se recibe por referencia (el hilo la recibe con std::ref)
void tareaTransmisionHilo(DispositivoComunicacion* dev, int& exitosas);

#endif
