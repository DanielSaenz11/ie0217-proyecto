/**
 * @file auxiliares.hpp
 * @brief Declaraciones de funciones auxiliares para la validación de entradas de datos.
 * @details Este archivo contiene la declaración de funciones que ayudan a validar fechas,
 *          números enteros, números decimales y formatos específicos como moneda y teléfono.
 *          Estas funciones se utilizan para asegurar que los datos ingresados sean válidos
 *          y cumplan con los formatos requeridos.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 08/11/2024
 */

#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP

#include <iostream>

/**
 * @brief Valida y obtiene una fecha en formato YYYY-MM-DD.
 * 
 * Esta función solicita una fecha al usuario y verifica que cumpla con el formato y
 * los límites de días y meses.
 * 
 * @return `std::string` La fecha validada en formato YYYY-MM-DD.
 */
std::string validarFecha();

/**
 * @brief Obtiene un número entero positivo del usuario.
 * 
 * Solicita un número entero al usuario y verifica que sea positivo y válido.
 * En caso de entrada no válida, solicita nuevamente el ingreso.
 * 
 * @return `int` El número entero positivo validado.
 */
int obtenerEntero();

/**
 * @brief Obtiene un número decimal positivo del usuario.
 * 
 * Solicita un número decimal al usuario y verifica que sea positivo y válido.
 * En caso de entrada no válida, solicita nuevamente el ingreso.
 * 
 * @return `double` El número decimal positivo validado.
 */
double obtenerDecimal();

/**
 * @brief Solicita y valida el tipo de moneda ingresado.
 * 
 * Presenta opciones de moneda al usuario ('USD' o 'CRC') y solicita una selección.
 * 
 * @return `std::string` La moneda seleccionada ('USD' o 'CRC').
 */
std::string validarMoneda();

/**
 * @brief Valida y obtiene un número de teléfono en formato ####-####.
 * 
 * Solicita un número de teléfono al usuario y verifica que cumpla con el formato
 * ####-####. En caso de formato incorrecto, solicita nuevamente el ingreso.
 * 
 * @return `std::string` El número de teléfono validado en formato ####-####.
 */
std::string validarTelefono();

/**
 * @brief Valida el ingreso de 's' o 'n' para operaciones donde se realizan preguntas binarias.
 * 
 * Solicita una respuesta de 's' o 'n' (case insensitive) hasta que se ingrese una válida.
 * 
 * @return `true` si se ingresó 's'; `false` para 'n'.
 */
bool validarRespuestaSN();

/**
 * @brief Valida el ingreso de un nombre de un archivo con extensión .csv.
 * 
 * Utiliza regex para validar el formato y solicita el ingreso del nombre hasta que se indique uno válido.
 * 
 * @return `std::string` El nombre del .csv ingresado.
 */
std::string obtenerArchivoCSV();

/**
 * @brief Calcula la potencia de un número.
 * 
 * Esta función eleva un número base a una potencia entera positiva, multiplicando
 * el número base por sí mismo tantas veces como lo indique el exponente.
 * 
 * @param n El número base que se va a elevar.
 * @param p El exponente al que se eleva el número base.
 * @return El resultado de n elevado a la potencia p.
 */
double potencia(double n, double p);

#endif // AUXILIARES_HPP