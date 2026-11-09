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
    void supervisar(DispositivoComunicacion* dev, int& transmisionesExitosas);
};

#endif 