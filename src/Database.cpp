

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