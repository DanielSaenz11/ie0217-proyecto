

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "constants.hpp"
#include "Cuenta.hpp"

// Función para mostrar el menú principal
void mostrarMenuPrincipal();

// Función para mostrar el menú de atención al cliente
void menuAtencionCliente(sqlite3* db);

// Función para mostrar el menú de operaciones de cliente autenticado
void menuOperacionesCliente(sqlite3* db, Cuenta& cuenta);

#endif // MENU_HPP