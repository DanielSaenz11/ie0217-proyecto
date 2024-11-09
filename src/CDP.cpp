/**
 * @file CDP.cpp
 * @author Rodrigo Madrigal Montes
 * @brief Archivo de implementación de los métodos para CDP
 * @version 1.0
 * @date 2024-11-07
 * 
 */

#include "CDP.hpp"
#include <iostream>

/**
 * @brief Definición del constructor de la clase CDP
 * 
 * @param idCuenta ID de la cuenta asocidada al CDP
 * @param deposito Monto del depósito
 * @param plazoMeses Plazo en meses del CDP
 * @param tasaInteres Tasa de interés anual del CDP
 * @param fechaSolicitud Fecha en la que se solicita el CDP
 */
CDP::CDP(int idCuenta, double deposito, int plazoMeses, double tasaInteres, const std::string &fechaSolicitud)
    : idCuenta(idCuenta), deposito(deposito), plazoMeses(plazoMeses), tasaInteres(tasaInteres), fechaSolicitud(fechaSolicitud) {}


/**
 * @brief Definición del método para crear un CDP en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @return true Si se pudo crear el CDP en la base de datos
 * @return false Si no se pudo crear el CDP en la base de datos
 */
bool CDP::crear(sqlite3* db) {

    std::string sql = "INSERT INTO CDP (idCuenta, deposito, plazoMeses, tasaInteres, fechaSolicitud) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idCuenta);
    sqlite3_bind_double(stmt, 2, deposito);
    sqlite3_bind_int(stmt, 3, plazoMeses);
    sqlite3_bind_double(stmt, 4, tasaInteres);
    sqlite3_bind_text(stmt, 5, fechaSolicitud.c_str(), -1, SQLITE_STATIC);

    bool exito = sqlite3_step(stmt) == SQLITE_DONE;
    if (exito) {
        int idCDP = sqlite3_last_insert_rowid(db);
        std::cout << "CDP creado con ID: " << idCDP << std::endl;
    }
    else {
        std::cerr << "Error al insertar en la base de datos: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return exito;
}

/**
 * @brief Definición del método estático para obtener un CDP de la base de datos
 * 
 * @param db Puntero a la base de datos
 * @param idCDP ID del CDP
 * @return Datos del CDP
 */
CDP CDP::obtener(sqlite3* db, int idCDP) {
    std::string sql = "SELECT idCuenta, deposito, plazoMeses, tasaInteres, fechaSolicitud FROM CDP WHERE idCDP = ?;";
    sqlite3_stmt* stmt;

    CDP cdp(0, 0.0, 0, 0.0, ""); // Crear instancia vacía de CDP

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return cdp; // Retornar objeto vacío
    }

    sqlite3_bind_int(stmt, 1, idCDP); // Asignar ID del CDP para la búsqueda en la consulta SQL

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        
        cdp.idCuenta = sqlite3_column_int(stmt, 0);
        cdp.deposito = sqlite3_column_double(stmt, 1);
        cdp.plazoMeses = sqlite3_column_int(stmt, 2);
        cdp.tasaInteres = sqlite3_column_double(stmt, 3);
        cdp.fechaSolicitud = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
    }
    else {
        std::cerr << "CDP no encontrado." << std::endl;
    }

    sqlite3_finalize(stmt);
    
    return cdp;
}
