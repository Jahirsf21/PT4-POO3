#ifndef VACUNA_HPP
#define VACUNA_HPP

#include <string>
#include "Patogeno.hpp"
#include <iostream>

class Vacuna {
private:
    std::string nombre;
    std::string pais;
    int dosis;
    Patogeno* patogeno_asociado;

public:
    Vacuna(std::string nombre, std::string pais, int dosis);
    void mostrar() const;
    std::string get_nombre() const;
    std::string get_pais() const;
    int get_dosis() const;
    void asociar_patogeno(Patogeno* patogeno);
    Patogeno* get_patogeno_asociado() const;
};

#endif
