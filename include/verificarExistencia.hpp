/**
 * @file verificarExistencia.hpp
 * @author Rodrigo Madrigal Montes
 * @brief Declaración de las funciones para verificar la existencia de registros
 * @version 1.0
 * @date 2024-11-05
 * 
 */
#ifndef EXISTENCE_CHECKS_HPP
#define EXISTENCE_CHECKS_HPP

#include <string>
#include <sqlite3.h>

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCliente Id del cliente sobre el que se quiere verificar
 * @return true Si el registro del cliente existe en la base de datos
 * @return false Si no existe el registro del cliente en la base de datos
 */
bool clienteExiste(sqlite3* db, int idCliente);

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCuenta Id de la cuenta que se quiere verificar
 * @return true Si el registro de la cuenta no existe en la base de datos
 * @return false 
 */
bool cuentaExiste(sqlite3* db, int idCuenta);

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idPrestamo Id del préstamo que se quiere verificar
 * @return true Si el registro del préstamo no existe en la base de datos
 * @return false 
 */
bool prestamoExiste(sqlite3* db, int idPrestamo);

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCDP Id del CDP que se quiere verificar
 * @return true Si el registro del CDP existe en la base de datos
 * @return false Si el registro del CDP no existe en la base de datos
 */
bool cdpExiste(sqlite3* db, int idCDP);


#endif // EXISTENCE_CHECKS_HPP