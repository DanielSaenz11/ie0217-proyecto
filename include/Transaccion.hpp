/**
 * @file Transaccion.hpp
 * @brief Declaración de la clase Transaccion para gestionar transacciones bancarias.
 * @details Este archivo contiene la definición de la clase Transaccion, que representa una
 *          operación financiera entre cuentas, como depósitos, retiros, transferencias,
 *          abonos a préstamos, y pagos de CDP. La clase maneja la información relevante
 *          de cada transacción y su procesamiento en la base de datos.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#ifndef TRANSACCION_HPP
#define TRANSACCION_HPP

#include <string>
#include <sqlite3.h>

/**
 * @class Transaccion
 * @brief Representa una transacción bancaria entre cuentas.
 * 
 * La clase Transaccion permite modelar una operación financiera entre dos cuentas,
 * como depósitos, retiros, transferencias, abonos a préstamos, y pagos de CDP. 
 * 
 * Cada transacción contiene información sobre la cuenta remitente, la cuenta
 * destinataria, el tipo de transacción y el monto. Además, proporciona
 * el método `procesar` para registrar la transacción en la base de datos.
 */
class Transaccion {
    private:
        /// @brief ID de la cuenta remitente
        int idRemitente;

        /// @brief ID de la cuenta destinataria
        int idDestinatario;

        /// @brief Tipo de transacción
        std::string tipo;

        /// @brief Monto de la transacción
        double monto;

    public:
        /**
         * @brief Constructor de la clase Transaccion.
         * 
         * Inicializa una transacción con la cuenta remitente, la cuenta destinataria,
         * el tipo de operación y el monto de la transacción.
         * 
         * @param idRemitente ID de la cuenta remitente.
         * @param idDestinatario ID de la cuenta destinataria.
         * @param tipo Tipo de transacción ('DEP' para depósito, 'RET' para retiro, 'TRA' para transaccion, 'ABO' para abono, 'CDP' para CDP).
         * @param monto Monto de la transacción.
         */
        Transaccion(int idRemitente, int idDestinatario, const std::string &tipo, double monto);
        
        /**
         * @brief Procesa la transacción en la base de datos.
         * 
         * Esta función ejecuta la transacción, al registrar los detalles de la operación en la base de datos.
         * Dependiendo del tipo de transacción, puede modificar los saldos de las cuentas involucradas.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @return `true` si la transacción se procesa correctamente; `false` en caso contrario.
         */
        bool procesar(sqlite3* db);
};

#endif // TRANSACCION_HPP
