/**
 * @file reportesCDP.cpp
 * @author Rodrigo Madrigal Montes
 * @brief Implementación de las funciones para generar reportes para un CDP
 * 
 * Pendiente de integración en clase CDP
 * 
 * @version 1.0
 * @date 2024-11-06
 * 
 */
#include <iostream>
#include "reportesCDP.hpp"
using namespace std;

/**
 * @brief Función para generar un reporte al solicitar un CDP
 * 
 * @param db Puntero a la base de datos
 * @param idCuenta Id de la cuenta remitente del CDP
 * @param monto Monto del CDP
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteSolicitudCDP(sqlite3* db, int idCuenta, double monto) {

    // Consulta a la base de datos
    const char* sql = "INSERT INTO Transacciones (idRemitente, idDestinatario, tipo, monto) "
                      "VALUES (?, NULL, 'CDP', ?);";

    // Se prepara la consulta y se emite un mensaje de error si falla
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta de solicitud CDP: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Se enlaza el ID de la cuenta y el monto en la consulta
    sqlite3_bind_int(stmt, 1, idCuenta); // ID del Remitente
    sqlite3_bind_double(stmt, 2, monto); // monto del CDP

    // Ejecutamos la inserción y verificamos si fue exitosa
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Ocurrió un error al insertar el registro en Transacciones: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);     // se libera la memoria del statement para evitar memory leaks
        return false;
    }

    // Se libera la memoria del statement
    sqlite3_finalize(stmt);
    cout << "Registro de solicitud de CDP agregado exitosamente en Transacciones." << endl;
    return true;
}

/**
 * @brief Función para generar un reporte al vencer un CDP
 * 
 * @param db Puntero a la base de datos
 * @param idCuenta Id de la cuenta remitente del CDP
 * @param monto Monto del CDP
 * @return true true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteVencimientoCDP(sqlite3* db, int idCuenta, double monto) {
    
    // Consulta a la base de datos
    const char* sql = "INSERT INTO Transacciones (idRemitente, idDestinatario, tipo, monto) "
                      "VALUES (NULL, ?, 'CDP', ?);";

    // Se prepara la consulta y se emite un mensaje de error si falla
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta de vencimiento CDP: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Se enlaza el ID de la cuenta y el monto en la consulta
    sqlite3_bind_int(stmt, 1, idCuenta); // ID del Destinatario
    sqlite3_bind_double(stmt, 2, monto); // monto del CDP mas los intereses 

    // Ejecutamos la inserción y verificamos si fue exitosa
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Ocurrió un error al insertar el registro en Transacciones: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);     // se libera la memoria del statement para evitar memory leaks
        return false;
    }

    // Se libera la memoria del statement 
    sqlite3_finalize(stmt);
    cout << "Registro de vencimiento de CDP agregado exitosamente en Transacciones." << endl;
    return true;
}

