/**
 * @file reportesCDP.cpp
 * @author Rodrigo Madrigal Montes
 * @brief Implementación de las funciones para generar reportes para un CDP
 * @version 1.0
 * @date 2024-11-06
 * 
 */
#include <iostream>
#include "reportesCDP.hpp"
using namespace std;

bool reporteSolicitudCDP(sqlite3* db) {
    const char* sql = "SELECT idCDP, idCuenta, deposito, tasaInteres, fechaSolicitud FROM CDP;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare16_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta" << sqlite3_errmsg(db) << endl;
        return false;        
    }

    ofstream file("reporteSolicitudCDP.csv");
    if (!file.is_open()) {
        cerr << "Ocurrió un error al abrir el archivo para escribir los reportes" << endl;
        return false;
    }

    file << "ID CDP,ID Cuenta,Deposito,Plazo en Meses,Tasa de Interes,Fecha de Solicitud\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idCDP = sqlite3_column_int(stmt, 0);
        int idCuenta = sqlite3_column_int(stmt, 1);
        double deposito = sqlite3_column_double(stmt, 2);
        int plazoMeses = sqlite3_column_int(stmt, 3);
        double tasaInteres = sqlite3_column_double(stmt, 4);
        const unsigned char* fechaSolictud = sqlite3_column_text(stmt, 5);

        file << idCDP << "," << idCuenta << "," << deposito << "," << plazoMeses << "," << tasaInteres << "," << fechaSolictud << "\n";
    }

    sqlite3_finalize(stmt);
    file.close();
    return true;

}

bool reporteVencimientoCDP(sqlite3* db, const string& fechaActual) {
    const char* sql = "SELECT idCDP, idCuenta, deposito, plazoMeses, tasaInteres, fechaSolicitud "
                      "FROM CDP WHERE date(fechaSolicitud, '+' || plazoMeses || ' months') <= date(?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta de vencimiento de CDPs: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, fechaActual.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        cerr << "Ocurrió un error al enlazar la fecha actual: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    ofstream file("reporte_vencimiento_CDPs.csv");
    if (!file.is_open()) {
        cerr << "Ocurrió un error al abrir el archivo para escribir los reportes." << endl;
        return false;
    }
    file << "ID CDP,ID Cuenta,Deposito,Plazo en Meses,Tasa de Interes,Fecha de Solicitud\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idCDP = sqlite3_column_int(stmt, 0);
        int idCuenta = sqlite3_column_int(stmt, 1);
        double deposito = sqlite3_column_double(stmt, 2);
        int plazoMeses = sqlite3_column_int(stmt, 3);
        double tasaInteres = sqlite3_column_double(stmt, 4);
        const unsigned char* fechaSolicitud = sqlite3_column_text(stmt, 5);

        file << idCDP << "," << idCuenta << "," << fixed << std::setprecision(2)
             << deposito << "," << plazoMeses << "," << tasaInteres << ","
             << fechaSolicitud << "\n";
    }

    sqlite3_finalize(stmt);
    file.close();
    return true;
}

