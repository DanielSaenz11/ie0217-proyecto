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
#include "auxiliares.hpp"

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

/**
 * @brief Función para generar el reporte del pago estimado de un préstamo
 * 
 * @param db Puntero a la base de datos
 * @param idPrestamo ID del préstamo del que se quiere generar el reporte 
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reportePagoEstimado(sqlite3* db, int idPrestamo) {
    
    // Variables que guardan el nombre del archivo donde se quiere guardar el reporte si así se desea
    std::string nombreArchivo;
    std::string guardarEnArchivo;

    // Consulta SQL para obtener los datos del préstamo
    const char* sql = "SELECT idPrestamo, idCliente, monto, tasaInteres, plazoMeses FROM Prestamos WHERE idPrestamo = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta del préstamo: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Vincular el ID del préstamo
    sqlite3_bind_int(stmt, 1, idPrestamo);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int idPrestamo = sqlite3_column_int(stmt, 0);
        int idCliente = sqlite3_column_int(stmt, 1);
        double monto = sqlite3_column_double(stmt, 2);
        double tasaInteres = sqlite3_column_double(stmt, 3);
        int plazoMeses = sqlite3_column_int(stmt, 4);

        // Llamada a la función auxiliar para calcular la cuota mensual
        double cuotaMensual = cuotaMensualPrestamo(monto, tasaInteres, plazoMeses);

        // Generar y mostrar el reporte en pantalla
        std::cout << "Reporte de Pago Estimado para el Préstamo\n";
        std::cout << "ID Préstamo: " << idPrestamo << "\n";
        std::cout << "ID Cliente: " << idCliente << "\n";
        std::cout << "Monto: $" << monto << "\n";
        std::cout << "Tasa de Interés: " << tasaInteres << "%\n";
        std::cout << "Plazo en Meses: " << plazoMeses << "\n";
        std::cout << "Cuota Mensual Estimada: $" << cuotaMensual << "\n";

        // Preguntar si se desea guardar en archivo CSV
        std::cout << "\n¿Desea guardar el reporte en un archivo CSV? (sí/no): ";
        std::cin >> guardarEnArchivo;

        if (guardarEnArchivo == "sí") {
            std::cout << "Ingrese el nombre del archivo (con extensión .csv): ";
            std::cin >> nombreArchivo;

            std::ofstream archivo(nombreArchivo);
            if (!archivo.is_open()) {
                std::cerr << "Error al abrir el archivo para escribir el reporte." << std::endl;
                sqlite3_finalize(stmt);
                return false;
            }

            archivo << "ID Préstamo,ID Cliente,Monto,Tasa de Interés,Plazo en Meses,Cuota Mensual Estimada\n";
            archivo << idPrestamo << "," << idCliente << "," << monto << ","
                    << tasaInteres << "," << plazoMeses << "," << cuotaMensual << "\n";

            archivo.close();
            std::cout << "Reporte guardado en: " << nombreArchivo << std::endl;
        }
    } else {
        std::cerr << "Préstamo no encontrado en la base de datos.\n";
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

