

#include <iostream>
#include "Database.hpp"
#include "constants.hpp"
#include "Menu.hpp"
#include "auxiliares.hpp"

int main() {
    Database db("banco.db"); // Conectar a la base de datos
    int opcionPrincipal;
    
    do {
        mostrarMenuPrincipal();
        opcionPrincipal = obtenerEntero();

        switch (static_cast<MenuPrincipalOpciones>(opcionPrincipal)) {
            case MenuPrincipalOpciones::ATENCION_CLIENTE:
                menuAtencionCliente(db.get()); // Llamar a la función del menú de atención al cliente
                break;
            case MenuPrincipalOpciones::PRESTAMO_BANCARIO:
                // Implementación de la sección de préstamo bancario.
                std::cout << "Funcionalidad de préstamo bancario en construcción." << std::endl;
                break;
            case MenuPrincipalOpciones::SALIR:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida en el menú principal." << std::endl;
                break;
        }
    } while (opcionPrincipal != static_cast<int>(MenuPrincipalOpciones::SALIR));
    
    return 0;
}
