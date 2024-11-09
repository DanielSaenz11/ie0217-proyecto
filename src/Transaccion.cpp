/**
 * @file Transaccion.cpp
 * @author Daniel Alberto Sáenz Obando
 * @brief Archivo de implementación de los métodos para las transacciones
 * @version 1.0
 * @date 2024-11-07
 * 
 */

#include "Transaccion.hpp"
#include <iostream>

/**
 * @brief Definición del constructor de la clase CDP
 * 
 * @param idRemitente ID de la cuenta remitente
 * @param idDestinatario ID de la cuenta destinataria
 * @param tipo Tipo de transacción
 * @param monto Monto de la transacción
 */
Transaccion::Transaccion(int idRemitente, int idDestinatario, const std::string &tipo, double monto)
    : idRemitente(idRemitente), idDestinatario(idDestinatario), tipo(tipo), monto(monto) {}

/**
 * @brief Definición del método para procesar una transaccion en la base de datos
 * 
 * @param db Puntero a la base de datos
 * @return true Si se pudo procesar y agregar la transacción en la base de datos
 * @return false Si no se pudo procesar y agregar la transacción en la base de datos
 */
bool Transaccion::procesar(sqlite3* db) {

    const char* sql = "INSERT INTO Transacciones (idRemitente, idDestinatario, tipo, monto) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de transacción: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Verificar si hay identificadores nulos
    if (idRemitente != -1) sqlite3_bind_int(stmt, 1, idRemitente); else sqlite3_bind_null(stmt, 1);
    if (idDestinatario != -1) sqlite3_bind_int(stmt, 2, idDestinatario); else sqlite3_bind_null(stmt, 2);

    sqlite3_bind_text(stmt, 3, tipo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, monto);

    bool exito = sqlite3_step(stmt) == SQLITE_DONE;
    if (!exito) {
        std::cerr << "Error al procesar transacción: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);

    return exito;
}