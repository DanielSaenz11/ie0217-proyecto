/**
 * @file PagoPrestamo.hpp
 * @brief Declaración de la clase PagoPrestamo para gestionar pagos de préstamos en la base de datos.
 * @details Este archivo contiene la definición de la clase PagoPrestamo, incluyendo su constructor y el método 
 *          para registrar un pago en la base de datos. La clase maneja atributos como el ID del pago, el ID del 
 *          préstamo asociado, la cuota pagada, el aporte al capital, el aporte a intereses y el saldo restante 
 *          después del pago.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#ifndef PAGOPRESTAMO_HPP
#define PAGOPRESTAMO_HPP

#include <sqlite3.h>
#include <string>

/**
 * @class PagoPrestamo
 * @brief Representa un pago realizado a un préstamo en el sistema.
 * 
 * Esta clase permite registrar y manejar los datos asociados a un pago de préstamo,
 * incluyendo la cuota pagada, los aportes al capital e intereses, y el saldo restante.
 */
class PagoPrestamo {
    private:
        /// @brief ID del pago.
        int idPagoPrestamo;

        /// @brief ID del préstamo asociado.
        int idPrestamo;

        /// @brief Cuota pagada en este pago.
        double cuotaPagada;

        /// @brief Monto del aporte al capital.
        double aporteCapital;

        /// @brief Monto del aporte a intereses.
        double aporteIntereses;

        /// @brief Saldo restante después del pago.
        double saldoRestante;

    public:
        /**
         * @brief Constructor de la clase PagoPrestamo.
         * 
         * Inicializa un nuevo objeto PagoPrestamo con los detalles del pago.
         * 
         * @param idPrestamo ID del préstamo asociado.
         * @param cuotaPagada Monto total de la cuota pagada.
         * @param aporteCapital Monto destinado al capital del préstamo.
         * @param aporteIntereses Monto destinado a los intereses del préstamo.
         * @param saldoRestante Saldo restante del préstamo después del pago.
         */
        PagoPrestamo(int idPrestamo, double cuotaPagada, double aporteCapital, double aporteIntereses, double saldoRestante);

        /**
         * @brief Crea un registro del pago en la base de datos.
         * 
         * Inserta los datos del pago en la tabla correspondiente de la base de datos.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @return `true` si el registro se crea correctamente, `false` en caso de error.
         */
        bool crear(sqlite3* db);
};

#endif // PAGO_PRESTAMO_HPP
