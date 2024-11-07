/**
 * @file reportesCDP.hpp
 * @author Rodrigo Madrigal Montes
 * @brief Declaración de las funciones para generar reportes para un CDP
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
 * @brief Función para generar un reporte de los CDP solicitados
 * 
 * @param db Puntero a la base de datos
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteSolicitudCDP(sqlite3* db);

/**
 * @brief Función para generar un reporte de los CDP vencidos hasta la fecha
 * 
 * @param db Puntero a la base de datos
 * @param fechaActual Fecha actual para generar el reporte
 * @return true Cuando se generó el reporte
 * @return false Si hubo un error al generar el reporte
 */
bool reporteVencimientoCDP(sqlite3* db, const string& fechaActual);


#endif // REPORTES_CDP_HPP