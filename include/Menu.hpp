/**
 * @file Menu.hpp
 * @brief Declaración de funciones para mostrar y gestionar los menús de la aplicación bancaria.
 * @details Este archivo contiene la declaración de funciones para mostrar los menús de la
 *          aplicación, incluyendo el menú principal, el menú de atención al cliente y el menú
 *          de operaciones de un cliente autenticado. Estas funciones permiten la interacción
 *          del usuario con las distintas opciones y funcionalidades del sistema. Además, se incluyen
 *          subfunciones de cada menú para realizar cada operación. 
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 28/11/2024
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
 * @brief Muestra y gestiona el menú de atención al cliente.
 * 
 * Permite al usuario iniciar sesión, registrar un cliente o regresar al menú principal.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void menuAtencionCliente(sqlite3* db);

/**
 * @brief Muestra las opciones del menú de atención al cliente.
 * 
 * Imprime las opciones disponibles y solicita una selección al usuario.
 * 
 * @return `void`
 */
void mostrarMenuAtencion();

/**
 * @brief Inicia sesión de un cliente.
 * 
 * Solicita la cédula del cliente, verifica la existencia del cliente en la base de datos
 * y permite gestionar las cuentas asociadas.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void iniciarSesionCliente(sqlite3* db);

/**
 * @brief Registra un nuevo cliente en el sistema.
 * 
 * Solicita los datos del cliente (cédula, nombre, apellidos, teléfono) y los almacena en la base de datos.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void registrarCliente(sqlite3* db);

/**
 * @brief Muestra y gestiona el menú de operaciones del cliente.
 * 
 * Ofrece opciones como ver saldo, realizar depósitos, transferencias, retiros y gestionar CDP.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Referencia a la cuenta del cliente actualmente en uso.
 * @return `void`
 */
void menuOperacionesCliente(sqlite3* db, Cuenta& cuenta);

/**
 * @brief Muestra las opciones del menú de operaciones del cliente.
 * 
 * Imprime las opciones disponibles y solicita una selección al usuario.
 * 
 * @return `void`
 */
void mostrarMenuOperaciones();


/**
 * @brief Gestiona las opciones relacionadas con CDP.
 * 
 * Permite solicitar un CDP, consultar su estado o regresar al menú de operaciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Referencia a la cuenta del cliente.
 * @return `void`
 */
void manejarCDP(sqlite3* db, Cuenta& cuenta);

/**
 * @brief Gestiona las opciones de abonos a préstamos.
 * 
 * Permite realizar abonos a préstamos propios o de terceros o regresar al menú de operaciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Referencia a la cuenta del cliente.
 * @return `void`
 */
void manejarAbonoPrestamo(sqlite3* db, Cuenta& cuenta);

/**
 * @brief Realiza un depósito en la cuenta.
 * 
 * Solicita el monto a depositar y lo agrega al saldo de la cuenta actual.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Referencia a la cuenta del cliente.
 * @return `void`
 */
void realizarDeposito(sqlite3* db, Cuenta& cuenta);

/**
 * @brief Realiza una transferencia entre cuentas.
 * 
 * Permite transferir un monto desde la cuenta actual a otra cuenta, verificando su existencia y moneda.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Referencia a la cuenta del cliente.
 * @return `void`
 */
void realizarTransferencia(sqlite3* db, Cuenta& cuenta);

/**
 * @brief Realiza un retiro de la cuenta.
 * 
 * Solicita el monto a retirar y lo deduce del saldo de la cuenta actual.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cuenta Referencia a la cuenta del cliente.
 * @return `void`
 */
void realizarRetiro(sqlite3* db, Cuenta& cuenta);

/**
 * @brief Muestra y gestiona el menú de préstamos.
 * 
 * Permite al usuario solicitar un préstamo, consultar los préstamos existentes o regresar al menú principal.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void menuPrestamos(sqlite3* db);

/**
 * @brief Muestra las opciones del menú de préstamos.
 * 
 * Imprime las opciones disponibles y solicita una selección al usuario.
 * 
 * @return `void`
 */
void mostrarMenuPrestamos();

/**
 * @brief Solicita un préstamo.
 * 
 * Permite al cliente seleccionar el tipo de préstamo, ajustar los valores predeterminados y crear el préstamo.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void solicitarPrestamo(sqlite3* db);

/**
 * @brief Consulta el estado de un préstamo.
 * 
 * Permite visualizar el estado de un préstamo específico y generar un archivo con su información.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void consultarPrestamos(sqlite3* db);


#endif // MENU_HPP