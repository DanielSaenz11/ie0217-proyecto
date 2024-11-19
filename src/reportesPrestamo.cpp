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
    try {
        const char* sql = "SELECT idPrestamo, idCliente, monto, tasaInteres, plazoMeses FROM Prestamos;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error al preparar la consulta: " + std::string(sqlite3_errmsg(db)));
        }

        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            throw std::ios_base::failure("Error al abrir el archivo para escribir el reporte.");
        }

        archivo << "ID Préstamo,ID Cliente,Monto,Tasa de Interés,Plazo en Meses\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int idPrestamo = sqlite3_column_int(stmt, 0);
            int idCliente = sqlite3_column_int(stmt, 1);
            double monto = sqlite3_column_double(stmt, 2);
            double tasaInteres = sqlite3_column_double(stmt, 3);
            int plazoMeses = sqlite3_column_int(stmt, 4);

            archivo << idPrestamo << "," << idCliente << "," << monto << "," 
                    << tasaInteres << "," << plazoMeses << "\n";
        }

        sqlite3_finalize(stmt);
        archivo.close();
        std::cout << "Reporte de solicitud de préstamo generado en: " << nombreArchivo << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error en reporteSolicitudPrestamo: " << e.what() << std::endl;
        return false;
    }
}



/**
 * @brief Función para generar el reporte al de los préstamos que finalizan
 * 
 * @param db Puntero a la base de datos
 * @param nombreArchivo Nombre del archivo donde se quiere generar el reporte
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteFinalizarPrestamo(sqlite3* db, const std::string& fechaVencimiento, const std::string& nombreArchivo) {
    try {
        std::string sql = "SELECT id, nombreCliente, monto, fechaVencimiento FROM Prestamos WHERE fechaVencimiento = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error al preparar la consulta: " + std::string(sqlite3_errmsg(db)));
        }

        sqlite3_bind_text(stmt, 1, fechaVencimiento.c_str(), -1, SQLITE_STATIC);

        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            throw std::ios_base::failure("Error al abrir el archivo para escribir el reporte.");
        }

        archivo << "ID,NombreCliente,Monto,FechaVencimiento\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* nombreCliente = sqlite3_column_text(stmt, 1);
            double monto = sqlite3_column_double(stmt, 2);
            const unsigned char* fecha = sqlite3_column_text(stmt, 3);

            archivo << id << "," << nombreCliente << "," << monto << "," << fecha << "\n";
        }

        sqlite3_finalize(stmt);
        archivo.close();
        std::cout << "Reporte de vencimiento de préstamos generado en: " << nombreArchivo << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error en reporteFinalizarPrestamo: " << e.what() << std::endl;
        return false;
    }
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
    try {
        std::string nombreArchivo;
        std::string guardarEnArchivo;

        const char* sql = "SELECT idPrestamo, idCliente, monto, tasaInteres, plazoMeses FROM Prestamos WHERE idPrestamo = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error al preparar la consulta del préstamo: " + std::string(sqlite3_errmsg(db)));
        }

        sqlite3_bind_int(stmt, 1, idPrestamo);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int idPrestamo = sqlite3_column_int(stmt, 0);
            int idCliente = sqlite3_column_int(stmt, 1);
            double monto = sqlite3_column_double(stmt, 2);
            double tasaInteres = sqlite3_column_double(stmt, 3);
            int plazoMeses = sqlite3_column_int(stmt, 4);

            double cuotaMensual = calcularCuotaMensual(monto, plazoMeses, tasaInteres);

            std::cout << "Reporte de Pago Estimado para el Préstamo\n";
            std::cout << "ID Préstamo: " << idPrestamo << "\n";
            std::cout << "ID Cliente: " << idCliente << "\n";
            std::cout << "Monto: $" << monto << "\n";
            std::cout << "Tasa de Interés: " << tasaInteres << "%\n";
            std::cout << "Plazo en Meses: " << plazoMeses << "\n";
            std::cout << "Cuota Mensual Estimada: $" << cuotaMensual << "\n";

            std::cout << "\n¿Desea guardar el reporte en un archivo CSV? (sí/no): ";
            std::cin >> guardarEnArchivo;

            if (guardarEnArchivo == "sí") {
                std::cout << "Ingrese el nombre del archivo (con extensión .csv): ";
                std::cin >> nombreArchivo;

                std::ofstream archivo(nombreArchivo);
                if (!archivo.is_open()) {
                    throw std::ios_base::failure("Error al abrir el archivo para escribir el reporte.");
                }

                archivo << "ID Préstamo,ID Cliente,Monto,Tasa de Interés,Plazo en Meses,Cuota Mensual Estimada\n";
                archivo << idPrestamo << "," << idCliente << "," << monto << ","
                        << tasaInteres << "," << plazoMeses << "," << cuotaMensual << "\n";

                archivo.close();
                std::cout << "Reporte guardado en: " << nombreArchivo << std::endl;
            }
        } else {
            throw std::runtime_error("Préstamo no encontrado en la base de datos.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error en reportePagoEstimado: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Función para calcular la cuota mensula a pagar para un préstamo
 * 
 * @param monto Monto del préstamo
 * @param plazo Plazo del préstamo
 * @param tasaInteres Tasa de interés del préstamo
 * @return double Monto de la cuota mensual
 */
double calcularCuotaMensual(double monto, int plazo, double tasaInteres) {
    
    double tasaInteresMensual = (tasaInteres/100) / 12;

    double a  = 1 + tasaInteresMensual;

    double cuotaMensual = (monto * tasaInteresMensual * potencia(a, plazo)) / (potencia(a, plazo) - 1);

    return cuotaMensual;
}

