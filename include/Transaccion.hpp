/**
 * @file Transaccion.hpp
 * @author Daniel Alberto Sáenz Obando
 * @brief Archivo de declaración de los métodos para las transacciones
 * @version 1.0
 * @date 2024-11-07
 * 
 */

#ifndef TRANSACCION_HPP
#define TRANSACCION_HPP

#include <string>
#include <sqlite3.h>

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

        /// @brief Declaración del constructor de la clase Transaccion
        /// @param idRemitente ID de la cuenta remitente
        /// @param idDestinatario ID de la cuenta destinataria
        /// @param tipo Tipo de transacción
        /// @param monto Monto de la transacción
        Transaccion(int idRemitente, int idDestinatario, const std::string &tipo, double monto);
        
        /// @brief Declaración del método para procesar una transaccion en la base de datos
        /// @param db Puntero a la base de datos
        /// @return Si se pudo procesar la transacción o no
        bool procesar(sqlite3* db);
};

#endif // TRANSACCION_HPP
