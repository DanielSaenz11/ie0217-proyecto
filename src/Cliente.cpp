/**
 * @file Cliente.cpp
 * @brief Implementación de la clase Cliente para gestionar datos de clientes en la base de datos.
 * @details Este archivo contiene la implementación de los métodos de la clase Cliente, que permite
 *          la creación, obtención y verificación de clientes en la base de datos SQLite.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 08/11/2024
 */

#include "Cliente.hpp"
#include "SQLiteStatement.hpp"
#include <iostream>
#include <limits>

// Constructor para inicializar un cliente con los datos proporcionados.
Cliente::Cliente(int cedula, const std::string &nombre, const std::string &primerApellido,
                 const std::string &segundoApellido, const std::string &telefono)
    : cedula(cedula), nombre(nombre), primerApellido(primerApellido), segundoApellido(segundoApellido), telefono(telefono) {}


// Función para crear un nuevo registro de cliente en la base de datos.
bool Cliente::crear(sqlite3* db) {
    // Verificar que no exista un cliente con el mismo número de cédula
    if (Cliente::existe(db, this->cedula)) {
        std::cerr << "Error: Ya existe un cliente con el número de cédula" << std::endl;
        return false;
    }

    // Consulta SQL para insertar un nuevo cliente en la base de datos
    const std::string sql = "INSERT INTO Clientes (cedula, nombre, primerApellido, segundoApellido, telefono) VALUES (?, ?, ?, ?, ?);";

    try {
        SQLiteStatement statement(db, sql);

        // Asignar valores a los parámetros de la consulta
        sqlite3_bind_int(statement.get(), 1, cedula);
        sqlite3_bind_text(statement.get(), 2, nombre.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement.get(), 3, primerApellido.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement.get(), 4, segundoApellido.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement.get(), 5, telefono.c_str(), -1, SQLITE_STATIC);

        // Ejecutar la inserción en la base de datos
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error al insertar en la base de datos: " + std::string(sqlite3_errmsg(db)));
        }

        // Obtener el ID del cliente recién insertado y asignarlo al atributo idCliente
        idCliente = sqlite3_last_insert_rowid(db);
        std::cout << "Cliente creado con ID: " << idCliente << std::endl;
        return true;

    } catch (const std::exception& e) {
        // Manejar errores y reportar mensajes en consola
        std::cerr << e.what() << std::endl;
        return false;
    }
}

// Función para obtener un cliente desde la base de datos por medio de su cédula
Cliente Cliente::obtener(sqlite3* db, int cedula) {
    // Consulta SQL para seleccionar datos del cliente a partir de su cédula
    std::string sql = "SELECT idCliente, nombre, primerApellido, segundoApellido, telefono FROM Clientes WHERE cedula = ?;";

    // Crear un cliente vacío que se retornará si no se encuentra el cliente en la base de datos
    Cliente cliente(0, "", "", "", "");

    try {
        SQLiteStatement statement(db, sql);

        // Asignar el valor de la cédula al parámetro de la consulta
        sqlite3_bind_int(statement.get(), 1, cedula);

        // Ejecutar la consulta y verificar si se encontró un registro
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Asignar los valores obtenidos de la base de datos al objeto cliente
            cliente.idCliente = sqlite3_column_int(statement.get(), 0);
            cliente.cedula = cedula;
            cliente.nombre = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 1));
            cliente.primerApellido = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 2));
            cliente.segundoApellido = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 3));
            cliente.telefono = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 4));
        } else {
            throw std::runtime_error("Error: Cliente no encontrado con la cédula ingresada.");
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return cliente;
}

// Función para verificar si existe un cliente en la base de datos con la cédula
bool Cliente::existe(sqlite3* db, int cedula) {
    // Consulta SQL para verificar la existencia de un cliente mediante su cédula
    const std::string sql = "SELECT COUNT(1) FROM Clientes WHERE cedula = ?;";

    try {
        // Utilizar SQLiteStatement para manejar el ciclo de vida del statement
        SQLiteStatement statement(db, sql);

        // Asignar el valor de la cédula al parámetro de la consulta
        sqlite3_bind_int(statement.get(), 1, cedula);

        // Ejecutar la consulta y obtener el resultado
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Retornar true si el resultado es mayor a 0
            return sqlite3_column_int(statement.get(), 0) > 0;
        } else {
            throw std::runtime_error("Error al ejecutar la consulta para verificar la existencia del cliente.");
        }

    } catch (const std::exception& e) {
        // Manejar errores y reportar mensajes en consola
        std::cerr << e.what() << std::endl;
        return false; // Retornar false en caso de error
    }
}

// Función que retorna la cédula del cliente
int Cliente::getCedula() const {
    return cedula;
}

// Función que retorna el identificador (ID) del cliente
int Cliente::getID() const {
    return idCliente;
}
