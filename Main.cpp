#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <set>
#include "Vacuna.hpp"
#include "Patogeno.hpp"

std::list<Vacuna> vacunas;
std::list<Patogeno> patogenos;

void agregar_vacuna(std::string nombre, std::string pais, int dosis);
void agregar_patogeno(std::string nombre);
void mostrar_vacunas();
void mostrar_patogenos();
void mostrar_primera_vacuna();
void mostrar_ultima_vacuna();
bool nombre_valido(std::string nombre);
bool pais_valido(std::string pais);
bool dosis_valida(int dosis);
void menu();
void estadisticas();
void pais_mas_dosis();
void vacunas_pais();
void asociar_patogeno_vacuna();
void paises_por_patogeno();

void agregar_patogeno(std::string nombre) {
    if (!nombre_valido(nombre)) {
        std::cout << "El nombre del patogeno no puede tener numeros\n";
        return;
    }
    Patogeno patogeno(nombre);
    patogenos.push_back(patogeno);
    std::cout << "Patogeno agregado correctamente\n";
    std::cout << "Nombre: " << nombre << "\n";
}

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

void mostrar_patogenos() {
    if (patogenos.empty()) {
        std::cout << "No hay patogenos registrados.\n";
        return;
    }
    std::cout << "====== PATOGENOS REGISTRADOS ======\n";
    int indice = 1;
    for (const auto& patogeno : patogenos) {
        std::cout << indice << ". ";
        patogeno.mostrar();
        indice++;
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

    for (auto iterador1 = vacunas.begin(); iterador1 != vacunas.end(); ++iterador1) {
        std::string vacuna_actual = iterador1->get_nombre();

        if (procesadas.find(vacuna_actual) != procesadas.end()) {
            continue;
        }

        procesadas.insert(vacuna_actual);

        int contador = 0;

        for (auto iterador2 = vacunas.begin(); iterador2 != vacunas.end(); ++iterador2) {
            if (iterador2->get_nombre() == vacuna_actual) {
                contador++;
            }
        }

        std::cout << vacuna_actual << ": " << contador << " paises\n";
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

void asociar_patogeno_vacuna() {
    if (vacunas.empty()) {
        std::cout << "No hay vacunas registradas.\n";
        return;
    }
    if (patogenos.empty()) {
        std::cout << "No hay patogenos registrados.\n";
        return;
    }

    std::cout << "====== VACUNAS DISPONIBLES ======\n";
    int indice = 1;
    for (const auto& vacuna : vacunas) {
        std::cout << indice << ". " << vacuna.get_nombre() << " (" << vacuna.get_pais() << ")\n";
        indice++;
    }

    int vacuna_seleccionada_num;
    while (true) {
        std::cout << "Seleccione el numero de vacuna: ";
        std::string entrada;
        std::getline(std::cin, entrada);
        try {
            vacuna_seleccionada_num = std::stoi(entrada);
            if (vacuna_seleccionada_num >= 1 && vacuna_seleccionada_num <= vacunas.size()) {
                break;
            } else {
                std::cout << "Numero de vacuna invalido. Intente nuevamente.\n";
            }
        } catch (std::invalid_argument& e) {
            std::cout << "Ingrese un numero valido.\n";
        }
    }

    std::cout << "\n====== PATOGENOS DISPONIBLES ======\n";
    mostrar_patogenos();

    int patogeno_seleccionado_num;
    while (true) {
        std::cout << "Seleccione el numero de patogeno: ";
        std::string entrada;
        std::getline(std::cin, entrada);
        try {
            patogeno_seleccionado_num = std::stoi(entrada);
            if (patogeno_seleccionado_num >= 1 && patogeno_seleccionado_num <= patogenos.size()) {
                break;
            } else {
                std::cout << "Numero de patogeno invalido. Intente nuevamente.\n";
            }
        } catch (std::invalid_argument& e) {
            std::cout << "Ingrese un numero valido.\n";
        }
    }

    int indice_actual = 1;
    Vacuna* vacuna_seleccionada = nullptr;
    for (auto& vacuna : vacunas) {
        if (indice_actual == vacuna_seleccionada_num) {
            vacuna_seleccionada = &vacuna;
            break;
        }
        indice_actual++;
    }

    indice_actual = 1;
    Patogeno* patogeno_seleccionado = nullptr;
    for (auto& patogeno : patogenos) {
        if (indice_actual == patogeno_seleccionado_num) {
            patogeno_seleccionado = &patogeno;
            break;
        }
        indice_actual++;
    }

    if (vacuna_seleccionada != nullptr && patogeno_seleccionado != nullptr) {
        vacuna_seleccionada->asociar_patogeno(patogeno_seleccionado);
        std::cout << "Patogeno '" << patogeno_seleccionado->getNombre() << "' asociado correctamente a la vacuna '" 
                  << vacuna_seleccionada->get_nombre() << "'\n";
    }
}

void paises_por_patogeno() {
    if (patogenos.empty()) {
        std::cout << "No hay patogenos registrados.\n";
        return;
    }
    if (vacunas.empty()) {
        std::cout << "No hay vacunas registradas.\n";
        return;
    }

    std::cout << "====== PAISES CON VACUNAS POR PATOGENO ======\n";
    
    for (const auto& patogeno : patogenos) {
        std::cout << "\nPatogeno: " << patogeno.getNombre() << "\n";
        std::cout << "Paises con vacunas disponibles:\n";
        
        std::set<std::string> paises_con_vacuna;
        bool encontrado = false;
        
        for (const auto& vacuna : vacunas) {
            if (vacuna.get_patogeno_asociado() != nullptr && 
                vacuna.get_patogeno_asociado()->getNombre() == patogeno.getNombre()) {
                paises_con_vacuna.insert(vacuna.get_pais());
                encontrado = true;
            }
        }
        
        if (encontrado) {
            for (const auto& pais : paises_con_vacuna) {
                std::cout << "- " << pais << "\n";
            }
        } else {
            std::cout << "No hay vacunas disponibles para este patogeno\n";
        }
    }
}

void estadisticas() {
    std::cout << "====== ESTADISTICAS ======\n";
    std::cout << "1. Pais con mas dosis\n";
    std::cout << "2. Vacunas por pais\n";
    std::cout << "3. Primera vacuna\n";
    std::cout << "4. Ultima vacuna\n";
    std::cout << "5. Paises con vacunas por patogeno\n";
    std::cout << "6. salir \n";
    std::cout << "Ingrese una opcion: ";
    std::string entrada;
    std::getline(std::cin, entrada);
    int opcion;
    try {
        opcion = std::stoi(entrada);
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
            paises_por_patogeno();
            estadisticas();
            break;
        case 6:
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
    std::cout << "2. Agregar patogeno\n";
    std::cout << "3. Asociar patogeno a vacuna\n";
    std::cout << "4. Mostrar vacunas\n";
    std::cout << "5. Mostrar patogenos\n";
    std::cout << "6. Estadisticas\n";
    std::cout << "7. Salir\n";
    std::cout << "Ingrese una opcion: ";
    std::string entrada;
    std::getline(std::cin, entrada);
    int opcion;
    try {
        opcion = std::stoi(entrada);
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
                std::string dosis_str;
                std::getline(std::cin, dosis_str);
                try {
                    dosis = std::stoi(dosis_str);
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
        case 2: {
            std::string nombre;
            while (true) {
                std::cout << "Ingrese el nombre del patogeno: ";
                std::getline(std::cin, nombre);
                if (nombre_valido(nombre)) break;
                std::cout << "El nombre no puede tener numeros\n";
            }
            agregar_patogeno(nombre);
            menu();
            break;
        }
        case 3:
            asociar_patogeno_vacuna();
            menu();
            break;
        case 4:
            mostrar_vacunas();
            menu();
            break;
        case 5:
            mostrar_patogenos();
            menu();
            break;
        case 6:
            if (!vacunas.empty()) {
                estadisticas();
            } else {
                std::cout << "No hay vacunas\n";
            }
            menu();
            break;
        case 7:
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