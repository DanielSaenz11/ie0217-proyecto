/**
 * @file main.cpp
 * @brief Punto de entrada principal para la aplicación bancaria.
 * @details Este archivo contiene la función principal `main` que gestiona la ejecución
 *          del programa. Conecta a la base de datos y presenta el menú principal al
 *          usuario, lo cual permite navegar entre las opciones de atención al cliente
 *          y préstamos bancarios.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#include <iostream>
#include "Database.hpp"
#include "constants.hpp"
#include "Menu.hpp"
#include "auxiliares.hpp"

/**
 * @brief Función principal de la aplicación.
 * 
 * Esta función es el punto de inicio de la aplicación bancaria. Conecta a la base de datos,
 * muestra el menú principal y permite al usuario seleccionar opciones para la atención
 * al cliente o información sobre préstamos bancarios. El programa continúa ejecutándose
 * hasta que el usuario seleccione la opción de salir.
 * 
 * @return `int` Código de estado de la ejecución del programa.
 */
int main() {
    Database db("banco.db"); // Conectar a la base de datos
    int opcionPrincipal;
    
    do {
        mostrarMenuPrincipal(); // Mostrar las opciones del menú principal
        opcionPrincipal = obtenerEntero(); // Obtener opción seleccionada por el usuario

        // Ejecutar acción correspondiente a la opción seleccionada en el menú principal
        switch (static_cast<MenuPrincipalOpciones>(opcionPrincipal)) {
            case MenuPrincipalOpciones::ATENCION_CLIENTE:
                menuAtencionCliente(db.get()); // Llamar a la función del menú de atención al cliente
                break;
            case MenuPrincipalOpciones::PRESTAMO_BANCARIO:
                // Implementación de la sección de préstamo bancario (en desarrollo).
                std::cout << "Funcionalidad de préstamo bancario en construcción." << std::endl;
                break;
            case MenuPrincipalOpciones::SALIR:
                // Mensaje de salida del programa
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                // Manejo de opción inválida
                std::cout << "Opción inválida en el menú principal." << std::endl;
                break;
        }
    } while (opcionPrincipal != static_cast<int>(MenuPrincipalOpciones::SALIR));
    
    return 0;
}
