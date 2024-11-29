/**
 * @file Cuenta.cpp
 * @brief Implementación de la clase PagoPrestamo para gestionar los pagos a prestamos en la base de datos.
 * @details Este archivo contiene la definición del método de la clase PagoPrestamo, que permiten
 *          crear el pago o abono a un préstamo almacenado en una base de datos SQLite.
 *          Se incluyen funcionalidades para realizar las validaciones de los datos necesario y 
 *          el manejo de errores correspondiente. 
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */
#include "PagoPrestamo.hpp"
#include "SQLiteStatement.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>


// Definición del constructor de la clase PagoPrestamo
PagoPrestamo::PagoPrestamo(int idPrestamo, double cuotaPagada, double aporteCapital, double aporteIntereses, double saldoRestante)
    : idPagoPrestamo(0), idPrestamo(idPrestamo), cuotaPagada(cuotaPagada), aporteCapital(aporteCapital),
      aporteIntereses(aporteIntereses), saldoRestante(saldoRestante) {}


// Definición de método público para registrar el pago de un préstamo
bool PagoPrestamo::crear(sqlite3* db) {
    try {
        // Consulta para insertar el pago en la tabla
        std::string sql = R"(
            INSERT INTO PagoPrestamos (idPrestamo, cuotaPagada, aporteCapital, aporteIntereses, saldoRestante)
            VALUES (?, ?, ?, ?, ?);
        )";

        // Crear statement y preparar la consulta
        SQLiteStatement statement(db, sql);

        // Asignar valores a los parámetros de la consulta
        sqlite3_bind_int(statement.get(), 1, idPrestamo);
        sqlite3_bind_double(statement.get(), 2, cuotaPagada);
        sqlite3_bind_double(statement.get(), 3, aporteCapital);
        sqlite3_bind_double(statement.get(), 4, aporteIntereses);
        sqlite3_bind_double(statement.get(), 5, saldoRestante);

        // Ejecutar la consulta
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error al ejecutar la consulta para registrar el pago: " + std::string(sqlite3_errmsg(db)));
        }

        // Obtener el ID generado (en caso de que se desee imprimir en una implementación después)
        idPagoPrestamo = sqlite3_last_insert_rowid(db);

        return true; // Operación exitosa

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        return false; // Operación fallida
    }
}
