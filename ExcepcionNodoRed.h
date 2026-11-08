#ifndef EXCEPCIONNODORED_H
#define EXCEPCIONNODORED_H

#include <stdexcept>
#include <string>

class ExcepcionNodoRed : public std::runtime_error {
    public:
        explicit ExcepcionNodoRed(const std::string& mensaje);
};

#endif
