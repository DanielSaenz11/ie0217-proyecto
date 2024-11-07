

#include "auxiliares.hpp"

#include <iostream>
#include <regex>
#include <limits>

std::string validarFecha() {
    std::string fecha;

    std::regex formatoFecha(R"((1|2)\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]))");

    while (true) {

        std::cin >> fecha;

        if (std::regex_match(fecha, formatoFecha)) {
            // Verificación adicional para días válidos según el mes
            int año = std::stoi(fecha.substr(0, 4));
            int mes = std::stoi(fecha.substr(5, 2));
            int dia = std::stoi(fecha.substr(8, 2));
            // Verificar días de febrero y años bisiestos
            if ((mes == 2 && dia <= (año % 4 == 0 && (año % 100 != 0 || año % 400 == 0) ? 29 : 28)) ||
                (mes == 4 || mes == 6 || mes == 9 || mes == 11 ? dia <= 30 : dia <= 31)) {
                return fecha;
            }
        }
        std::cout << "Error: Fecha inválida. Inténtelo de nuevo.\n";
    }
}

int obtenerEntero() {
    int numero;

    while (true) {
        std::cin >> numero;

        if (std::cin.fail() || numero <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Entrada inválida. Por favor ingrese un número entero positivo.\n";
        } else {
            return numero;
        }
    }
}

double obtenerDecimal() {
    double numero;
    while (true) {
        std::cin >> numero;

        if (std::cin.fail() || numero <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Entrada inválida. Por favor ingrese un número decimal positivo.\n";
        } else {
            return numero;
        }
    }
}

std::string validarMoneda() {
    int opcion;
    do {
        std::cout << "Seleccione el tipo de moneda:\n1. USD\n2. CRC\nOpción: ";
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor ingrese 1 o 2.\n";
        }
    } while (opcion != 1 && opcion != 2);

    return opcion == 1 ? "USD" : "CRC";
}

std::string validarTelefono() {
    std::string telefono;
    std::regex formatoTelefono(R"(\d{4}-\d{4})");
    while (true) {
        std::cout << "Ingrese un número de teléfono (####-####): ";
        std::cin >> telefono;

        if (std::regex_match(telefono, formatoTelefono)) {
            return telefono;
        }
        std::cout << "Error: Número de teléfono inválido. Inténtelo de nuevo.\n";
    }
}
