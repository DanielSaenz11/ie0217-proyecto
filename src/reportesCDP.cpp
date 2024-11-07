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

/**
 * @brief Función para generar un reporte de los CDP solicitados
 * 
 * @param db Puntero a la base de datos
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteSolicitudCDP(sqlite3* db) {

    /*Comando para la solicitud SQL */
    const char* sql = "SELECT idCDP, idCuenta, deposito, tasaInteres, fechaSolicitud FROM CDP;";

    /*Se prepara el statement para la consulta, y si hay un error al prepararlo se imprime este mensaje de error*/
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta" << sqlite3_errmsg(db) << endl;
        return false;        
    }

    /*Se abre el archivo "reporteSolicitudCDP.csv" para escribir el reporte, y si hubiera un error igualmente se 
    muestra un mensaje de error y se libera la memoria del statement para evitar memory leaks*/
    ofstream file("reporteSolicitudCDP.csv");
    if (!file.is_open()) {
        cerr << "Ocurrió un error al abrir el archivo para escribir los reportes" << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    /*Primero se escribe el encabezado en el archivo de reportes*/
    file << "ID CDP,ID Cuenta,Deposito,Plazo en Meses,Tasa de Interes,Fecha de Solicitud\n";

    /*Para cada fila que coincide con la busqueda se escribe en el archivo de reportes*/
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idCDP = sqlite3_column_int(stmt, 0);
        int idCuenta = sqlite3_column_int(stmt, 1);
        double deposito = sqlite3_column_double(stmt, 2);
        int plazoMeses = sqlite3_column_int(stmt, 3);
        double tasaInteres = sqlite3_column_double(stmt, 4);
        const unsigned char* fechaSolictud = sqlite3_column_text(stmt, 5);

        file << idCDP << "," << idCuenta << "," << deposito << "," << plazoMeses << "," << tasaInteres << "," << fechaSolictud << "\n";
    }

    /*Se libera la memoria del statement y se cierra el archivo*/
    sqlite3_finalize(stmt);
    file.close();

    cout << "El reporte de solicitud de CDP se ha generado en el archivo reporteSolicitudCDP.csv" << endl;
    return true;
}

/**
 * @brief Función para generar un reporte de los CDP vencidos hasta la fecha
 * 
 * @param db Puntero a la base de datos
 * @param fechaActual Fecha actual para generar el reporte
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteVencimientoCDP(sqlite3* db, const string& fechaActual) {

    /*Comando para la solicitud SQL */
    const char* sql = "SELECT idCDP, idCuenta, deposito, plazoMeses, tasaInteres, fechaSolicitud "
                      "FROM CDP WHERE date(fechaSolicitud, '+' || plazoMeses || ' months') <= date(?);";

    /*Se prepara el statement para la consulta, y si hay un error al prepararlo se imprime este mensaje de error*/
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ocurrió un error al preparar la consulta de vencimiento de CDPs: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    /*Se enlaza la fecha actual con el parámetro que recibe la consulta y si hay un error al hacerlo se 
    lanza un mensaje de error y se libera el statement para evitar memory leaks*/
    if (sqlite3_bind_text(stmt, 1, fechaActual.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        cerr << "Ocurrió un error al enlazar la fecha actual: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    /*Se abre el archivo "reporteVencimientoCDP.csv" para escribir el reporte, y si hubiera un error igualmente se 
    muestra un mensaje de error y se libera la memoria del statement para evitar memory leaks*/
    ofstream file("reporteVencimientoCDP.csv");
    if (!file.is_open()) {
        cerr << "Ocurrió un error al abrir el archivo para escribir los reportes." << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    /*Se escribe el encabezado en el archivo de reportes*/
    file << "ID CDP,ID Cuenta,Deposito,Plazo en Meses,Tasa de Interes,Fecha de Solicitud\n";

    /*Para cada fila que coincide con la busqueda se escribe en el archivo de reportes*/
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idCDP = sqlite3_column_int(stmt, 0);
        int idCuenta = sqlite3_column_int(stmt, 1);
        double deposito = sqlite3_column_double(stmt, 2);
        int plazoMeses = sqlite3_column_int(stmt, 3);
        double tasaInteres = sqlite3_column_double(stmt, 4);
        const unsigned char* fechaSolicitud = sqlite3_column_text(stmt, 5);

        file << idCDP << "," << idCuenta << "," << fixed << setprecision(2)
             << deposito << "," << plazoMeses << "," << tasaInteres << ","
             << fechaSolicitud << "\n";
    }

    /*Se libera la memoria del statement y se cierra el archivo*/
    sqlite3_finalize(stmt);
    file.close();

    cout << "El reporte de vencimiento de CDP se ha generado en el archivo reporteVencimientoCDP.csv" << endl;
    return true;
}

