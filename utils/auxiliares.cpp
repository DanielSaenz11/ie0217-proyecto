/**
 * @file auxiliares.cpp
 * @brief Implementación de funciones auxiliares para la validación de datos.
 * @details Este archivo contiene la implementación de funciones de validación de fechas,
 *          números enteros, decimales, selección de moneda y formatos de teléfono.
 *          Estas funciones aseguran que los datos ingresados cumplen con el formato esperado
 *          antes de ser utilizados en el programa principal.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 08/11/2024
 */

#include "auxiliares.hpp"

#include <iostream>
#include <regex>
#include <limits>

std::string validarFecha() {
    // Declaración de string para almacenar la fecha
    std::string fecha;

    // Declaración de expresión regular para validar el formato correcto solicitado
    std::regex formatoFecha(R"((1|2)\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]))");

    while (true) {
        // Realizar el ingreso de la fecha
        std::cin >> fecha;

        // Validación con el regex
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
        // Mensaje de error para formato incorrecto
        std::cout << "Error: Fecha inválida. Inténtelo de nuevo.\n";
    }
}

int obtenerEntero() {
    int numero; // Declaración de número entero a validar

    while (true) {
        std::cin >> numero;

        // Validar si la entrada es un número entero positivo
        if (std::cin.fail() || numero <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar la entrada no válida
            std::cout << "Error: Entrada inválida. Por favor ingrese un número entero positivo.\n";
        } else {
            return numero; // Retornar el número si cumple con el formato solicitado
        }
    }
}

double obtenerDecimal() {
    double numero; // Declaración de número con decimales a validar

    while (true) {
        std::cin >> numero; // Entrada del número

        // Validar si la entrada es un número decimal positivo
        if (std::cin.fail() || numero <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar la entrada no válida
            std::cout << "Error: Entrada inválida. Por favor ingrese un número decimal positivo.\n";
        } else {
            return numero; // Retornar el número si cumple con el formato solicitado
        }
    }
}

std::string validarMoneda() {
    int opcion; // Opción que representa la selección de moneda
    
    do {
        std::cout << "Seleccione el tipo de moneda:\n1. USD\n2. CRC\nOpción: ";
        std::cin >> opcion;

        // Validar si la opción ingresada es válida
        if (std::cin.fail()) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar entrada no válida
            std::cout << "Error: Entrada inválida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 1 && opcion != 2); // Continuar solicitando hasta obtener una opción válida

    return opcion == 1 ? "USD" : "CRC"; // Retornar la moneda seleccionada por medio del operador ternario
}

std::string validarTelefono() {
    std::string telefono; // String que representa el número de teléfono
    
    // Expresión regular que valida el formato del teléfono
    std::regex formatoTelefono(R"(\d{4}-\d{4})");

    while (true) {
        std::cout << "Ingrese un número de teléfono (####-####): ";
        std::cin >> telefono;

        // Verificar si el formato es válido
        if (std::regex_match(telefono, formatoTelefono)) {
            return telefono;
        }

        std::cout << "Error: Número de teléfono inválido. Inténtelo de nuevo.\n";
    }
}

double potencia(double n, double p) {
    double resultado = 1;

    // Multiplicar la base n por sí misma p veces
    for (int i = 1; i <=p; i++) {
        resultado *= n;
    }

    return resultado; // Retornar resultado correspondiente a la exponenciación
}

