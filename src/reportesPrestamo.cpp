/**
 * @file reportesPrestamo.cpp
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @brief Implementación de las funciones para generar reportes de Préstamos
 * @version 1.0
 * @date 2024-11-18
 * 
 */
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <string>
#include <iomanip>

/**
 * @brief Función para generar el reporte al solicitar un préstamo
 * 
 * @param db Puntero a la base de datos
 * @param nombreArchivo Nombre del archivo donde se quiere generar el reporte
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteSolicitudPrestamo(sqlite3* db, const std::string& nombreArchivo) {
    // Consulta SQL para obtener los préstamos y pagos realizados
    const char* sql = 
        "SELECT P.idPrestamo, P.idCliente, P.montoTotal, P.plazoMeses, PP.numeroCuota, "
        "PP.capitalPagado, PP.interesesPagados "
        "FROM Prestamos P "
        "JOIN PagoPrestamos PP ON P.idPrestamo = PP.idPrestamo "
        "ORDER BY P.idPrestamo, PP.numeroCuota;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Abrir archivo CSV para el reporte
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir el reporte." << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Encabezado en formato CSV
    archivo << "ID Préstamo,ID Cliente,Monto Total,Plazo Meses,Número Cuota,Capital Pagado,Intereses Pagados\n";

    // Leer cada fila y escribir los datos en el archivo CSV
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idPrestamo = sqlite3_column_int(stmt, 0);
        int idCliente = sqlite3_column_int(stmt, 1);
        double montoTotal = sqlite3_column_double(stmt, 2);
        int plazoMeses = sqlite3_column_int(stmt, 3);
        int numeroCuota = sqlite3_column_int(stmt, 4);
        double capitalPagado = sqlite3_column_double(stmt, 5);
        double interesesPagados = sqlite3_column_double(stmt, 6);

        // Escribir los datos en formato CSV
        archivo << idPrestamo << ","
                << idCliente << ","
                << std::fixed << std::setprecision(2) << montoTotal << ","
                << plazoMeses << ","
                << numeroCuota << ","
                << capitalPagado << ","
                << interesesPagados << "\n";
    }

    // Finalizar y cerrar
    sqlite3_finalize(stmt);
    archivo.close();

    std::cout << "Reporte de solicitud de préstamo generado en: " << nombreArchivo << std::endl;
    return true;
}


/**
 * @brief Función para generar el reporte al de los préstamos que finalizan
 * 
 * @param db Puntero a la base de datos
 * @param nombreArchivo Nombre del archivo donde se quiere generar el reporte
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteFinalizarPrestamo(sqlite3* db, const std::string& nombreArchivo) {
    // Consulta SQL para obtener los préstamos que están en el último mes del plazo
    const char* sql = 
        "SELECT P.idPrestamo, P.idCliente, P.montoTotal, P.plazoMeses, PP.numeroCuota, "
        "PP.capitalPagado, PP.interesesPagados "
        "FROM Prestamos P "
        "JOIN PagoPrestamos PP ON P.idPrestamo = PP.idPrestamo "
        "WHERE PP.numeroCuota = P.plazoMeses "
        "ORDER BY P.idPrestamo;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Abrir archivo CSV para el reporte
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir el reporte." << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Encabezado en formato CSV
    archivo << "ID Préstamo,ID Cliente,Monto Total,Plazo Meses,Última Cuota,Capital Pagado,Intereses Pagados\n";

    // Iterar sobre los resultados de la consulta y escribir en CSV
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int idPrestamo = sqlite3_column_int(stmt, 0);
        int idCliente = sqlite3_column_int(stmt, 1);
        double montoTotal = sqlite3_column_double(stmt, 2);
        int plazoMeses = sqlite3_column_int(stmt, 3);
        int numeroCuota = sqlite3_column_int(stmt, 4);
        double capitalPagado = sqlite3_column_double(stmt, 5);
        double interesesPagados = sqlite3_column_double(stmt, 6);

        archivo << idPrestamo << ","
                << idCliente << ","
                << std::fixed << std::setprecision(2) << montoTotal << ","
                << plazoMeses << ","
                << numeroCuota << ","
                << capitalPagado << ","
                << interesesPagados << "\n";
    }

    // Finalizar y cerrar
    sqlite3_finalize(stmt);
    archivo.close();

    std::cout << "Reporte de vencimiento de préstamos generado en: " << nombreArchivo << std::endl;
    return true;
}

