#ifndef SUPERVISORRED_H
#define SUPERVISORRED_H

#include "DispositivoComunicacion.h"

using namespace std;

class SupervisorRed {
public:
    SupervisorRed() = default;
    void supervisar(DispositivoComunicacion* dev, int& transmisionesExitosas);
};

#endif 