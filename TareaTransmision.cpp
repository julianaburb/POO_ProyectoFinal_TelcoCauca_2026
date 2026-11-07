#include "TareaTransmision.h"
#include "Registro.h"
#include <stdexcept>
#include <string>
#include <mutex>

void tareaTransmisionHilo(DispositivoComunicacion* dev, int& exitosas) {
    try {
        // Guarda defensiva contra punteros nulos
        if (dev == nullptr) {
            throw std::invalid_argument("ERROR: Puntero nulo pasado al hilo.");
        }

        // Invocacion polimorfica del metodo virtual (ligadura tardia por la vtable)
        dev->transmitir();
        registrarEventoSeguro("Transmision exitosa del dispositivo: " + dev->getId()
                              + " (" + dev->getTipo() + ")");

        // Variable compartida protegida con lock_guard
        // las llaves son para que el lock se suelte apenas se suma
        {
            std::lock_guard<std::mutex> lock(mtx_contador);
            ++exitosas;
        }
    }
    // primero la especifica y despues la general, como vimos en clase
    catch (const std::invalid_argument& e) {
        registrarEventoSeguro(std::string("[Argumento Invalido] EXCEPCION EN HILO: ") + e.what());
    }
    catch (const std::exception& e) {
        // Captura y aislamiento de la excepcion dentro del hilo
        // si se escapa del hilo el programa se cae con std::terminate()
        registrarEventoSeguro(std::string("[Excepcion Generica] EXCEPCION EN HILO: ") + e.what());
    }
}
