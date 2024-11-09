

#include "Prestamo.hpp"
#include <iostream>

// Definición del constructor de la clase Prestamo
Prestamo::Prestamo(int idCuenta, const std::string &tipo, double monto, double tasaInteres, int plazoMeses)
    : idCuenta(idCuenta), tipo(tipo), monto(monto), tasaInteres(tasaInteres), plazoMeses(plazoMeses), cuotaMensual(0), capitalPagado(0), interesesPagados(0), saldoRestante(monto), activo(true) {}



bool Prestamo::existe(sqlite3* db, int idPrestamo) {
    const std::string sql = "SELECT COUNT(1) FROM Prestamos WHERE idPrestamo = ?;";
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ocurrió un error al preparar la consulta para Prestamo: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idPrestamo);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists;
}