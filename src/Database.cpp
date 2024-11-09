/**
 * @file Database.cpp
 * @brief Implementación de la clase Database para gestionar la conexión a la base de datos.
 * @details Este archivo contiene la implementación de los métodos de la clase Database, 
 *          que permite abrir y cerrar una conexión a la base de datos SQLite.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @date 08/11/2024
 * @copyright MIT License
 */

#include "Database.hpp"
#include <iostream>

// Definición del constructor de la clase Database
Database::Database(const std::string &nombreDB) {
    // Abrir la base de datos a partir de su nombre
    if (sqlite3_open(nombreDB.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Definición de destructor de la clase Database
Database::~Database() {
    // Cerrar la base de datos
    if (db) {
        sqlite3_close(db);
    }
}

// Definición de función para obtener la conexión a la base de datos
sqlite3* Database::get() const {
    return db;
}