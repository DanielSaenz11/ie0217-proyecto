/**
 * @file Cliente.cpp
 * @brief Implementación de la clase Cliente para gestionar datos de clientes en la base de datos.
 * @details Este archivo contiene la implementación de los métodos de la clase Cliente, que permite
 *          la creación, obtención y verificación de clientes en la base de datos SQLite.
 * 
 * Software bajo la licencia de MIT.
 * En términos generales, se concede permiso para utilizar este Software sin ninguna restricción, pero se proporciona sin
 * ninguna garantía. 
 * El aviso de copyright anterior y este aviso de permiso deberán incluirse en todas
 * las copias o partes sustanciales del Software.
 * 
 * @author Daniel Alberto Sáenz Obando y Rodrigo Madrigal Montes
 * @date 08/11/2024
 */

#include "Cliente.hpp"
#include <iostream>

// Constructor para inicializar un cliente con los datos proporcionados.
Cliente::Cliente(int cedula, const std::string &nombre, const std::string &primerApellido,
                 const std::string &segundoApellido, const std::string &telefono)
    : cedula(cedula), nombre(nombre), primerApellido(primerApellido), segundoApellido(segundoApellido), telefono(telefono) {}


// Función para crear un nuevo registro de cliente en la base de datos.
bool Cliente::crear(sqlite3* db) {

    // Verificar que no exista un cliente con el mismo número de cédula.
    if (Cliente::existe(db, this->cedula)) {
        std::cout << "Error: Ya existe un cliente con el número de cédula" << std::endl;
        return false; // Salir de la función si el cliente ya existe
    }

    // Consulta SQL para insertar un nuevo cliente en la base de datos
    std::string sql = "INSERT INTO Clientes (cedula, nombre, primerApellido, segundoApellido, telefono) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt; // Declaración del statement

    // Preparar la consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Liberar memoria del statement en caso de error
        return false;
    }

    // Asignar valores a los parámetros de la consulta
    sqlite3_bind_int(stmt, 1, cedula);
    sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, primerApellido.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, segundoApellido.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, telefono.c_str(), -1, SQLITE_STATIC);

    // Ejecutar la inserción en la base de datos
    bool exito = (sqlite3_step(stmt) == SQLITE_DONE);

    if (exito) {
        // Obtener el ID del cliente recién insertado y asignarlo al atributo idCliente
        idCliente = sqlite3_last_insert_rowid(db);
        std::cout << "Cliente creado con ID: " << idCliente << std::endl;
    } else {
        std::cerr << "Error al insertar en la base de datos: " << sqlite3_errmsg(db) << std::endl;
    }
    
    sqlite3_finalize(stmt); // Liberar memoria del statement

    return exito; // Retornar estado de inserción
}

// Función para obtener un cliente desde la base de datos por medio de su cédula
Cliente Cliente::obtener(sqlite3* db, int cedula) {
    // Consulta SQL para seleccionar datos del cliente a partir de su cédula
    std::string sql = "SELECT idCliente, nombre, primerApellido, segundoApellido, telefono FROM Clientes WHERE cedula = ?;";
    sqlite3_stmt* stmt;

    // Crear un cliente vacío que se retornará si no se encuentra el cliente en la base de datos
    Cliente cliente(0, "", "", "", "");

    // Preparar la consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Liberar memoria del statement en caso de error
        return cliente; // Salir y retornar cliente vacío en caso de error
    }

    // Asignar el valor de la cédula al parámetro de la consulta
    sqlite3_bind_int(stmt, 1, cedula);

    // Ejecutar la consulta y verificar si se encontró un registro
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Asignar los valores obtenidos de la base de datos al objeto cliente
        cliente.idCliente = sqlite3_column_int(stmt, 0);
        cliente.cedula = cedula;
        cliente.nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cliente.primerApellido = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        cliente.segundoApellido = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        cliente.telefono = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
    } else {
        std::cerr << "Error: Cliente no encontrado con cédula ingresada." << std::endl;
    }

    sqlite3_finalize(stmt); // Liberar memoria del statement
    return cliente; // Retornar el objeto cliente (vacío si no se encontró)
}

// Función para verificar si existe un cliente en la base de datos con la cédula
bool Cliente::existe(sqlite3* db, int cedula) {
    // Consulta SQL para verificar la existencia de un cliente mediante su cédula
    const std::string sql = "SELECT COUNT(1) FROM Clientes WHERE cedula = ?;";
    sqlite3_stmt* stmt;

    // Condición de existencia
    bool existe = false;

    // Preparar la consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ocurrió un error al preparar la consulta para Cliente: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Liberar memoria del statement en caso de error
        return false;
    }

    // Asignar el valor de la cédula al parámetro de la consulta
    sqlite3_bind_int(stmt, 1, cedula);

    // Ejecutar la consulta y obtener el resultado de existencia
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0); // Almacenar el resultado en la variable existe
    }

    sqlite3_finalize(stmt); // Liberar memoria del statement
    
    return existe; // Retornar el resultado de existencia
}

// Función que retorna la cédula del cliente
int Cliente::getCedula() const {
    return cedula;
}

// Función que retorna el identificador (ID) del cliente
int Cliente::getID() const {
    return idCliente;
}
