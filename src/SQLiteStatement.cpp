/**
 * @file SQLiteStatement.cpp
 * @brief Implementación de la clase SQLiteStatement para gestionar las consultas SQL en la base de datos.
 * @details Este archivo contiene la definición del constructor y destrcutor de la clase PagoPrestamo, además de
 *          poder obtener la consulta preparada de la misma clase. 
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#include "SQLiteStatement.hpp"

#include <sqlite3.h>

// Definición del constructor de la clase para el SQLite stmt
SQLiteStatement::SQLiteStatement(sqlite3* db, const std::string& query) : stmt_(nullptr) {
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt_, nullptr) != SQLITE_OK) {
        // Limpia stmt_ antes de lanzar la excepción
        if (stmt_ != nullptr) {
            sqlite3_finalize(stmt_); // Liberar memoria si hubo errores en el constructor
            stmt_ = nullptr; // Apuntar stmt a nullptr para evitar accesos fuera de límites
        }
        // Levantar error de runtime
        throw std::runtime_error("Error al preparar la consulta: " + std::string(sqlite3_errmsg(db)));
    }
}

// Definición de destructor de la clase SQLiteStatement
SQLiteStatement::~SQLiteStatement() {
    // Si stmt_ es distinto de nullptr, se libera la memoria
    if (stmt_ != nullptr) {
        sqlite3_finalize(stmt_);
    }
}

sqlite3_stmt* SQLiteStatement::get() const {
    return stmt_; // Retorna el statement preparado
}