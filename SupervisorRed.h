#ifndef SUPERVISORRED_H
#define SUPERVISORRED_H

#include <mutex>
#include "DispositivoComunicacion.h"

using namespace std;

class SupervisorRed {
private:
    std::mutex mtxConsola;

public:
    SupervisorRed() = default;

    // Función miembro para ejecución en std::thread (Sección 2.4)
    void supervisar(DispositivoComunicacion* dev, int& transmisionesExitosas);
};

#endif // SUPERVISORRED_H