/**
 * @file CDP.hpp
 * @author Daniel Alberto Sáenz Obando
 * @brief Archivo de declaración de los métodos para CDP
 * @version 1.0
 * @date 2024-11-07
 * 
 */

#ifndef CDP_HPP
#define CDP_HPP

#include <string>
#include <sqlite3.h>

class CDP {
    private:

        /// @brief ID propio del CDP
        int idCDP;

        /// @brief ID de la cuenta asocidada al CDP
        int idCuenta;

        /// @brief Monto del depósito
        double deposito;

        /// @brief Plazo en meses del CDP
        int plazoMeses;

        /// @brief Tasa de interés anual del CDP
        double tasaInteres;

        /// @brief Fecha en la que se solicita el CDP
        std::string fechaSolicitud;

    public:

        /// @brief Declaración del constructor de la clase CDP
        /// @param idCuenta ID de la cuenta asocidada al CDP
        /// @param deposito Monto del depósito
        /// @param plazoMeses Plazo en meses del CDP
        /// @param tasaInteres Tasa de interés anual del CDP
        /// @param fechaSolicitud Fecha en la que se solicita el CDP
        CDP(int idCuenta, double deposito, int plazoMeses, double tasaInteres, const std::string &fechaSolicitud);

        /// @brief Declaración del método para crear un CDP en la base de datos
        /// @param db Puntero a la base de datos
        /// @return Mensaje si se creó correctamente el CDP o no
        bool crear(sqlite3* db);

        /// @brief Declaración del método estático para obtener un CDP de la base de datos
        /// @param db Puntero a la base de datos
        /// @param idCDP ID del CDP
        /// @return Los datos del CDP
        static CDP obtener(sqlite3* db, int idCDP);
};

#endif // CDP_HPP
