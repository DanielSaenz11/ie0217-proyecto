/**
 * @file reportesCDP.hpp
 * @author Rodrigo Madrigal Montes
 * @brief Declaración de las funciones para generar reportes para un CDP
 * 
 * Pendiente de integración en clase CDP
 * 
 * @version 1.0
 * @date 2024-11-06
 * 
 */
#ifndef REPORTES_CDP_HPP
#define REPORTES_CDP_HPP

#include <sqlite3.h>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

/**
 * @brief Función para generar un reporte al solicitar un CDP
 * 
 * @param db Puntero a la base de datos
 * @param idCuenta Id de la cuenta remitente del CDP
 * @param monto Monto del CDP
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteSolicitudCDP(sqlite3* db, int idCuenta, double monto);

/**
 * @brief Función para generar un reporte al vencer un CDP
 * 
 * @param db Puntero a la base de datos
 * @param idCuenta Id de la cuenta remitente del CDP
 * @param monto Monto del CDP
 * @return true true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteVencimientoCDP(sqlite3* db, int idCuenta, double monto);


#endif // REPORTES_CDP_HPP