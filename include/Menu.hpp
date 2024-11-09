/**
 * @file Menu.hpp
 * @brief Declaración de funciones para mostrar y gestionar los menús de la aplicación bancaria.
 * @details Este archivo contiene la declaración de funciones para mostrar los menús de la
 *          aplicación, incluyendo el menú principal, el menú de atención al cliente y el menú
 *          de operaciones de un cliente autenticado. Estas funciones permiten la interacción
 *          del usuario con las distintas opciones y funcionalidades del sistema.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "constants.hpp"
#include "Cuenta.hpp"

/**
 * @brief Muestra el menú principal de la aplicación.
 * 
 * Esta función despliega el menú principal en pantalla y permite al usuario
 * seleccionar entre las opciones de atención al cliente, información sobre préstamos bancarios
 * o salir de la aplicación.
 * 
 * @return `void`
 */
void mostrarMenuPrincipal();

/**
 * @brief Muestra el menú de atención al cliente.
 * 
 * Esta función permite la interacción del usuario en el menú de atención al cliente,
 * donde puede iniciar sesión con un cliente existente o registrar un nuevo cliente en la base de datos.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void menuAtencionCliente(sqlite3* db);

/**
 * @brief Muestra el menú de operaciones para un cliente autenticado.
 * 
 * Esta función permite al usuario realizar varias operaciones en una cuenta
 * autenticada, como ver saldo, consultar historial de transacciones, solicitar un CDP,
 * realizar abonos a préstamos, depósitos, transferencias, y retiros.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Objeto Cuenta autenticada sobre la que se realizarán las operaciones.
 * @return `void`
 */
void menuOperacionesCliente(sqlite3* db, Cuenta& cuenta);

#endif // MENU_HPP