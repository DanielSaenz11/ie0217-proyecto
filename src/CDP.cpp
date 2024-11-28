

#include "CDP.hpp"
#include <iostream>
#include <string>

// Definición del constructor de la clase CDP
CDP::CDP(int idCuenta, const std::string &moneda, double deposito, int plazoMeses, double tasaInteres)
    : idCuenta(idCuenta), moneda(moneda), deposito(deposito), plazoMeses(plazoMeses), tasaInteres(tasaInteres) {}


// Definición de función para calcular el monto de intereses ganados al final del CDP
double CDP::interesGanado() const {
    return deposito * tasaInteres * plazoMeses;
}

// Definición de método para crear el CDP
bool CDP::crear(sqlite3* db) {
    std::string sql = R"(
        INSERT INTO CDP (idCuenta, moneda, deposito, plazoMeses, tasaInteres)
        VALUES (?, ?, ?, ?, ?);
    )";

    try {
        SQLiteStatement statement(db, sql);

        // Asociar los valores a la consulta preparada
        sqlite3_bind_int(statement.get(), 1, idCuenta);
        sqlite3_bind_text(statement.get(), 2, moneda.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(statement.get(), 3, deposito);
        sqlite3_bind_int(statement.get(), 4, plazoMeses);
        sqlite3_bind_double(statement.get(), 5, tasaInteres);

        // Ejecutar la consulta
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error: No se pudo insertar el CDP en la base de datos.");
        }

        idCDP = sqlite3_last_insert_rowid(db);
        std::cout << "CDP creado con éxito. ID: " << idCDP << std::endl;

        return true; // Creación exitosa
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false; // Creación fallida
    }
}


// Definición de método para obtener un CDP de la base de datos
CDP CDP::obtener(sqlite3* db, int idCDP) {
    // Consulta SQL para obtener los datos del CDP
    std::string sql = "SELECT idCuenta, moneda, deposito, plazoMeses, tasaInteres FROM CDP WHERE idCDP = ?;";

    // Crear instancia vacía de CDP
    CDP cdp(0, "", 0.0, 0, 0.0);

    try {
        // Crear instancia de SQLiteStatement para manejar el statement
        SQLiteStatement statement(db, sql);

        // Asignar ID del CDP como parámetro de la consulta
        sqlite3_bind_int(statement.get(), 1, idCDP);

        // Ejecutar la consulta y verificar si se encontró el registro
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Asignar los valores obtenidos a la instancia de CDP
            cdp.idCDP = idCDP;
            cdp.idCuenta = sqlite3_column_int(statement.get(), 0);
            cdp.moneda = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 1));
            cdp.deposito = sqlite3_column_double(statement.get(), 2);
            cdp.plazoMeses = sqlite3_column_int(statement.get(), 3);
            cdp.tasaInteres = sqlite3_column_double(statement.get(), 4);
        } else {
            // Lanzar excepción si no se encuentra el registro
            throw std::runtime_error("Error: CDP no encontrado con el ID especificado.");
        }
    } catch (const std::exception& e) {
        // Manejar errores y reportar en consola
        std::cerr << e.what() << std::endl;
    }

    return cdp;
}


int CDP::getID() const {
    return idCDP;
}

// Función para mostrar la información básica del CDP en el menú al consultar su estado
void CDP::mostrarInformacion() const {
    // Imprime los datos del CDP con formato tabular
    std::cout << "\n=== Estado del CDP ===" << std::endl;
    std::cout << std::left << std::setw(20) << "ID del CDP:" << idCDP << std::endl;
    std::cout << std::left << std::setw(20) << "ID de la Cuenta:" << idCuenta << std::endl;
    std::cout << std::left << std::setw(20) << "Moneda:" << moneda << std::endl;
    std::cout << std::left << std::setw(20) << "Monto:" << deposito << std::endl;
    std::cout << std::left << std::setw(20) << "Plazo en Meses:" << plazoMeses << std::endl;
    std::cout << std::left << std::setw(20) << "Tasa de Interés:" << tasaInteres << std::endl;
}