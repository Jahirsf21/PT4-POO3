#include "Vacuna.hpp"
#include "Patogeno.hpp"
#include <iostream>
#include <string>

Vacuna::Vacuna(std::string nombre, std::string pais, int dosis) {
    this->nombre = nombre;
    this->pais = pais;
    this->dosis = dosis;
}

void Vacuna::mostrar() const {
    std::cout << "====== VACUNA ======\n";
    std::cout << "Nombre: " << this->nombre << "\n";
    std::cout << "Pais: " << this->pais << "\n";
    std::cout << "Dosis: " << this->dosis << "\n";
    if (this->patogeno_asociado != nullptr) {
        std::cout << "Patogeno asociado: " << this->patogeno_asociado->getNombre() << "\n";
    }  else {
        std::cout << "No hay patogeno asociado\n";
    }
}

std::string Vacuna::get_nombre() {
    return this->nombre;
}

std::string Vacuna::get_pais() {
    return this->pais;
}

int Vacuna::get_dosis() const {
    return this->dosis;
}

void Vacuna::asociar_patogeno(Patogeno* patogeno) {
    this->patogeno_asociado = patogeno;
}

Patogeno* Vacuna::get_patogeno_asociado() const {
    return this->patogeno_asociado;
}


