#include "Torre.h"
#include <iostream>
#include "Antena.h"

Torre::Torre(std::string _id, std::string _ubic, double _alt)
    : idTorre(_id), ubicacion(_ubic), alturaMetros(_alt) {}

void Torre::agregarAntena(Antena* a) {
    if (a != nullptr) {
        listaAntenas.push_back(a);
    }
}


int Torre::contarAntenas5G() const { // excribo el cuerpo del metodo pedido
    int contador = 0;
    for (const auto& antenaPtr: listaAntenas) {
        if (antenaPtr!= nullptr && antenaPtr->getTecnologia().find("5G") !=std::string::npos) {
          contador++;
    }
  } return contador;
}

void Torre::mostrarReporteTorre() const {
    std::cout << "==================================================" << std::endl;
    std::cout << "ESTACIÓN BASE TORRE: " << idTorre << " | Ubicación: " << ubicacion
              << " (" << alturaMetros << "m)" << std::endl;
    std::cout << "Antenas Instaladas (" << listaAntenas.size() << "):" << std::endl;

    // Recorrido moderno range-based for sobre vector de punteros

    for (const auto& antenaPtr : listaAntenas) { 
        if (antenaPtr != nullptr) {
            antenaPtr->mostrarDetalles();
        }
    }
    std::cout << "Antenas 5G instaladas: " << contarAntenas5G() << std::endl; //muestro el resultado del metodo pedido en la consola
    std::cout << "==================================================" << std::endl;
}
