#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <set>
#include "Vacuna.hpp"

std::list<Vacuna> vacunas;

void agregar_vacuna(std::string nombre, std::string pais, int dosis);
void agregar_patogeno(std::string nombre);
void mostrar_vacunas();
void mostrar_primera_vacuna();
void mostrar_ultima_vacuna();
bool nombre_valido(std::string nombre);
bool pais_valido(std::string pais);
bool dosis_valida(int dosis);
void menu();
void estadisticas();
void pais_mas_dosis();
void vacunas_pais();

void agregar_vacuna(std::string nombre, std::string pais, int dosis) {
    if (!nombre_valido(nombre)) {
        std::cout << "El nombre no puede tener numeros\n";
        return;
    }
    if (!pais_valido(pais)) {
        std::cout << "El pais no puede tener numeros\n";
        return;
    }
    if (!dosis_valida(dosis)) {
        std::cout << "La dosis debe ser un numero entero mayor a 0\n";
        return;
    }
    Vacuna vacuna(nombre, pais, dosis);
    vacunas.push_back(vacuna);
    std::cout << "Vacuna agregada correctamente\n";
    std::cout << "Nombre: " << nombre << " | Pais: " << pais << " | Dosis: " << dosis << "\n";
}

bool nombre_valido(std::string nombre) {
    for (size_t i = 0; i < nombre.size(); ++i) {
        if (std::isdigit(nombre[i])) {
            return false;
        }
    }
    return true;
}

bool pais_valido(std::string pais) {
    for (size_t i = 0; i < pais.size(); ++i) {
        if (std::isdigit(pais[i])) {
            return false;
        }
    }
    return true;
}

bool dosis_valida(int dosis) {
    return dosis > 0;
}

void mostrar_vacunas() {
    for (const auto& vacuna : vacunas) {
        vacuna.mostrar();
    }
}

void pais_mas_dosis() {
    if (vacunas.empty()) {
        std::cout << "No hay vacunas registradas.\n";
        return;
    }

    std::list<Vacuna> copiaVacunas = vacunas;
    copiaVacunas.sort([](const Vacuna& a, const Vacuna& b) {
        return a.get_dosis() > b.get_dosis();
    });

    std::cout << "Pais con mas dosis aplicadas: " << copiaVacunas.front().get_pais()
              << " | Se han aplicado: " << copiaVacunas.front().get_dosis() << " dosis.\n";
}

void vacunas_pais() {
    if (vacunas.empty()) {
        std::cout << "No hay vacunas registradas.\n";
        return;
    }

    std::cout << "Cantidad de paises por vacuna:\n";

    std::set<std::string> procesadas;

    for (auto it1 = vacunas.begin(); it1 != vacunas.end(); ++it1) {
        std::string vacunaActual = it1->get_nombre();

        if (procesadas.find(vacunaActual) != procesadas.end()) {
            continue;
        }

        procesadas.insert(vacunaActual);

        int contador = 0;

        for (auto it2 = vacunas.begin(); it2 != vacunas.end(); ++it2) {
            if (it2->get_nombre() == vacunaActual) {
                contador++;
            }
        }

        std::cout << vacunaActual << ": " << contador << " paises\n";
    }
}

void mostrar_primera_vacuna() {
    std::cout << "====== PRIMERA VACUNA ======\n";
    vacunas.front().mostrar();
}

void mostrar_ultima_vacuna() {
    std::cout << "====== ULTIMA VACUNA ======\n";
    vacunas.back().mostrar();
}

void estadisticas() {
    std::cout << "====== ESTADISTICAS ======\n";
    std::cout << "1. Pais con mas dosis\n";
    std::cout << "2. Vacunas por pais\n";
    std::cout << "3. Primera vacuna\n";
    std::cout << "4. Ultima vacuna\n";
    std::cout << "5. salir \n";
    std::string op;
    std::getline(std::cin, op);
    int opcion;
    try {
        opcion = std::stoi(op);
    } catch (std::invalid_argument& e) {
        std::cout << "Opcion invalida\n";
        estadisticas();
        return;
    }
    switch (opcion) {
        case 1:
            pais_mas_dosis();
            estadisticas();
            break;
        case 2:
            vacunas_pais();
            estadisticas();
            break;
        case 3:
            mostrar_primera_vacuna();
            estadisticas();
            break;
        case 4:
            mostrar_ultima_vacuna();
            estadisticas();
            break;
        case 5:
            break;
        default:
            std::cout << "Opcion invalida\n";
            estadisticas();
            break;
    }

}

void menu() {
    std::cout << "====== MENU ======\n";
    std::cout << "1. Agregar vacuna\n";
    std::cout << "2. Mostrar vacunas\n";
    std::cout << "3. Estadisticas\n";
    std::cout << "4. Salir\n";
    std::cout << "Ingrese una opcion: ";
    std::string op;
    std::getline(std::cin, op);
    int opcion;
    try {
        opcion = std::stoi(op);
    } catch (std::invalid_argument& e) {
        std::cout << "Opcion invalida\n";
        menu();
        return;
    }
    switch (opcion) {
        case 1: {
            std::string nombre;
            std::string pais;
            int dosis;
            while (true) {
                std::cout << "Ingrese el nombre de la vacuna: ";
                std::getline(std::cin, nombre);
                if (nombre_valido(nombre)) break;
                std::cout << "El nombre no puede tener numeros\n";
            }
            while (true) {
                std::cout << "Ingrese el pais de la vacuna: ";
                std::getline(std::cin, pais);
                if (pais_valido(pais)) break;
                std::cout << "El pais no puede tener numeros\n";
            }
            while (true) {
                std::cout << "Ingrese el numero de dosis de la vacuna: ";
                std::string d;
                std::getline(std::cin, d);
                try {
                    dosis = std::stoi(d);
                    if (dosis_valida(dosis)) break;
                    else std::cout << "La dosis debe ser mayor a 0\n";
                } catch (std::invalid_argument& e) {
                    std::cout << "La dosis debe ser un numero entero\n";
                }
            }
            agregar_vacuna(nombre, pais, dosis);
            menu();
            break;
        }
        case 2:
            mostrar_vacunas();
            menu();
            break;
        case 3:
            if (!vacunas.empty()) {
                estadisticas();
            } else {
                std::cout << "No hay vacunas\n";
            }
            menu();
            break;
        case 4:
            break;
        default:
            std::cout << "Opcion invalida\n";
            menu();
            break;
    }
}


int main() {
    menu();
}