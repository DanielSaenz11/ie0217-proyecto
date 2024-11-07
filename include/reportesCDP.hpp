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

bool reporteSolicitudCDP(sqlite3* db);

bool reporteVencimientoCDP(sqlite3* db, const string& fechaActual);


#endif // REPORTES_CDP_HPP