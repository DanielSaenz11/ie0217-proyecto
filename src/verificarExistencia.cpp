/**
 * @file verificarExistencia.cpp
 * @author Rodrigo Madrigal Montes
 * @brief Implementación de las funciones para verificar la existencia de registros
 * @version 1.0
 * @date 2024-11-06
 * 
 */
#include "verificarExistencia.hpp"
#include <iostream>
using namespace std;

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCliente Id del cliente sobre el que se quiere verificar
 * @return true Si el registro del cliente existe en la base de datos
 * @return false Si no existe el registro del cliente en la base de datos
 */
bool clienteExiste(sqlite3* db, int idCliente) {

    /*Plantilla de la consulta que recibe un parámetro que será el idCliente que se proveee como parámetro*/
    const string sql = "SELECT COUNT(1) FROM Clientes WHERE idCliente = ?;";
    sqlite3_stmt* stmt;
    bool exists = false;

    /*Verifica si sucede un error al preparar la consulta se imprime este mensaje de error*/
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta para Cliente: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    /*Se utiliza la función 'bind_int' para pasarle a la consulta previamente declarada el
    parámetro idCliente para realizar la verificación*/
    sqlite3_bind_int(stmt, 1, idCliente);

    /*Por medio de la función 'step' se ejecuta la consulta con la configuración que se estableció 
    previamente, y retorna el numero de registros que coinciden con la consulta y asigna
    este valor a exists*/
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    /*Destructor del 'stmt' para liberar la memoria ocupada por el mismo*/
    sqlite3_finalize(stmt);
    return exists;
}

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCuenta Id de la cuenta que se quiere verificar
 * @return true Si el registro de la cuenta no existe en la base de datos
 * @return false 
 */
bool cuentaExiste(sqlite3* db, int idCuenta) {
    const string sql = "SELECT COUNT(1) FROM Cuentas WHERE idCuenta = ?;";
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta para Cuenta: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idCuenta);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists;
}

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idPrestamo Id del préstamo que se quiere verificar
 * @return true Si el registro del préstamo no existe en la base de datos
 * @return false 
 */
bool prestamoExiste(sqlite3* db, int idPrestamo) {
    const string sql = "SELECT COUNT(1) FROM Prestamos WHERE idPrestamo = ?;";
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta para Prestamo: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idPrestamo);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists;
}

/**
 * @brief Función para verificar si un cliente existe en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCDP Id del CDP que se quiere verificar
 * @return true Si el registro del CDP existe en la base de datos
 * @return false Si el registro del CDP no existe en la base de datos
 */
bool cdpExiste(sqlite3* db, int idCDP) {
    const string sql = "SELECT COUNT(1) FROM CDP WHERE idCDP = ?;";
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta para CDP: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idCDP);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists;
}

