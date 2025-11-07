#ifndef PATOGENO_HPP
#define PATOGENO_HPP

#include <iostream>
#include <string>

class Patogeno {
    private:
        std::string nombre;

    public:
        Patogeno(std::string nombre);

        void mostrar() const;

        std::string getNombre() const;
};

#endif