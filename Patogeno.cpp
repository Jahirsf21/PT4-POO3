#include "Patogeno.hpp"
#include <iostream>
#include <string>

Patogeno::Patogeno(std::string nombre) {
    this->nombre = nombre;
}

void Patogeno::mostrar() const {
    std::cout << "Nombre: " << this->nombre << "\n";
}

std::string Patogeno::getNombre() const {
    return this->nombre;
}