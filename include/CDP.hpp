/**
 * @file CDP.hpp
 * @brief Declaración de la clase CDP para gestionar certificados de depósito a plazo (CDP) en la base de datos.
 * @details Este archivo contiene la definición de la clase CDP, incluyendo su constructor y métodos para crear 
 *          un CDP en la base de datos y obtener información de un CDP existente. La clase maneja atributos como 
 *          el ID del CDP, el monto del depósito, el plazo en meses, la tasa de interés y la fecha de solicitud.
 * 
 * @authors Daniel Alberto Sáenz Obando
 *          Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#ifndef CDP_HPP
#define CDP_HPP

#include "SQLiteStatement.hpp"
#include <sqlite3.h>
#include <fstream>
#include <iomanip>
#include <string>

/**
 * @class CDP
 * @brief Clase para representar un Certificado de Depósito a Plazo (CDP).
 * 
 * Esta clase encapsula la lógica relacionada con los CDP, permitiendo su creación,
 * consulta y generación de reportes. Los CDP están asociados a una cuenta bancaria y tienen
 * atributos como depósito, plazo en meses, tasa de interés y fecha de solicitud.
 */
class CDP {
    private:

        /// @brief ID propio del CDP
        int idCDP = 0;

        /// @brief ID de la cuenta asocidada al CDP
        int idCuenta;

        /// @brief Moneda del CDP
        std::string moneda;

        /// @brief Monto del depósito
        double deposito;

        /// @brief Plazo en meses del CDP
        int plazoMeses;

        /// @brief Tasa de interés anual del CDP
        double tasaInteres;

        /**
         * @brief Calcula el interés ganado con el CDP al final del plazo
         * 
         * @return `double` Monto ganado.
         */
        double interesGanado() const;

    public:
        /**
         * @brief Declaración del constructor de la clase CDP
         * 
         * @param idCuenta ID de la cuenta asocidada al CDP.
         * @param moneda Tipo de moneda del CDP ('CRC', 'USD').
         * @param deposito Monto del depósito.
         * @param plazoMeses Plazo en meses del CDP.
         * @param tasaInteres Tasa de interés anual del CDP.
         * @param fechaSolicitud Fecha en la que se solicita el CDP.
         */
        CDP(int idCuenta, const std::string &moneda, double deposito, int plazoMeses, double tasaInteres);

        
        /**
         * @brief Crea un CDP en la base de datos en la tabla CDP.
         * 
         * @param db Puntero a la base de datos.
         * @return `true` si se creó correctamente el CDP, `false` en caso contrario.
         */
        bool crear(sqlite3* db);

        /**
         * @brief Método estático para obtener un CDP de la base de datos.
         * 
         * @param db Puntero a la base de datos.
         * @param idCDP ID del CDP.
         * @return `CDP` Objeto CDP que coincide con el id ingresado.
         */
        static CDP obtener(sqlite3* db, int idCDP);

        /**
         * @brief Muestra la información del CDP en formato tabular en la terminal al consultar
         * su estado en el menú.
         * 
         * @return `void`
         */
        void mostrarInformacion() const;

        /**
         * @brief Retorna el ID del certificado de depósito a plazo.
         * 
         * @return `int` ID del CDP.
         */
        int getID() const;

};

#endif // CDP_HPP
