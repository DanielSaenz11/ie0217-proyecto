/**
 * @file Transaccion.cpp
 * @brief Implementación de la clase Transaccion para el procesamiento de transacciones bancarias.
 * @details Este archivo contiene la implementación de los métodos de la clase Transaccion,
 *          que maneja las operaciones financieras entre cuentas, como depósitos, retiros,
 *          transferencias, abonos a préstamos y pagos de CDP, para registrar cada transacción en
 *          la base de datos.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#include "Transaccion.hpp"
#include <iostream>

// Definición del constructor de la clase Transaccion
Transaccion::Transaccion(int idRemitente, int idDestinatario, const std::string &tipo, double monto)
    : idRemitente(idRemitente), idDestinatario(idDestinatario), tipo(tipo), monto(monto) {}

// Definición de método para procesar una transacción en la base de datos
bool Transaccion::procesar(sqlite3* db) {
    // Consulta SQL para la inserción
    const char* sql = "INSERT INTO Transacciones (idRemitente, idDestinatario, tipo, monto) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    // Preparación de consulta SQL
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de transacción: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Liberar memoria del stmt
        return false; // Salir
    }

    // Verificar si hay identificadores nulos
    if (idRemitente != -1) sqlite3_bind_int(stmt, 1, idRemitente); else sqlite3_bind_null(stmt, 1);
    if (idDestinatario != -1) sqlite3_bind_int(stmt, 2, idDestinatario); else sqlite3_bind_null(stmt, 2);

    // Agregar tipo de transacción y monto al stmt
    sqlite3_bind_text(stmt, 3, tipo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, monto);

    // Ejecutar el comando SQL y obtener su código de salida
    bool exito = sqlite3_step(stmt) == SQLITE_DONE;
    if (!exito) {
        // Si ocurrió un error
        std::cerr << "Error al procesar transacción: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt); // Liberar memoria del stmt

    return exito; // Retornar estado de transacción
}