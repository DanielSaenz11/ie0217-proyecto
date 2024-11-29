/**
 * @file Prestamo.hpp
 * @brief Declaración de la clase Prestamo para la gestión de préstamos en la base de datos.
 * @details Este archivo define la clase Prestamo, que permite crear, gestionar y consultar información relacionada con préstamos bancarios.
 *          La clase maneja atributos clave como el monto, tipo de préstamo, tasa de interés, plazo, estado del préstamo, y cálculos 
 *          asociados como cuotas mensuales, intereses y abonos. También incluye métodos para interactuar con la base de datos, 
 *          consultar el estado del préstamo y generar reportes de pagos estimados.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */
#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

#include "Cuenta.hpp"
#include "constants.hpp"
#include <string>
#include <sqlite3.h>

/**
 * @class Prestamo
 * @brief Clase que representa un préstamo bancario.
 * 
 * La clase encapsula la lógica relacionada con los préstamos, permitiendo su creación,
 * consulta, abono y reporte. Los préstamos están asociados a cuentas bancarias y tienen
 * atributos como monto, plazo, tasa de interés y estado.
 */
class Prestamo {
    private:
        /// @brief Identificador del préstamo
        int idPrestamo = 0;

        /// @brief Identificador de la cuenta
        int idCuenta;

        /// @brief Tipo de préstamo: 'PER' (personal), 'PRE' (prendario), 'HIP' (hipotecario)
        std::string tipo;

        /// @brief Tipo de moneda del préstamo: 'CRC' o 'USD'.
        std::string moneda;

        /// @brief Monto solicitado del préstamo
        double monto;

        /// @brief Tasa de intéres del préstamo
        double tasaInteres;

        /// @brief Plazo para el que fue solicitado el préstamo
        int plazoMeses;

        /// @brief Cuota mensual a pagar
        double cuotaMensual;

        /// @brief Cuotas pagadas hasta el momento
        int cuotasPagadas;

        /// @brief Capital total pagado hasta el momento
        double capitalPagado;

        /// @brief Intereses pagados hasta el momento
        double interesesPagados;

        /// @brief Saldo restante a pagar
        double saldoRestante;

        /// @brief Estado de actividad del préstamo: true si no ha sido pagado totalmente y false en caso contrario
        bool activo;

        /// @brief Método privado para calcular el los intereses a pagar en el préstamo 
        /// @return Intereses a pagar del préstamo
        double calcularIntereses();

    public:
        /**
         * @brief Constructor de la clase Prestamo.
         * 
         * Inicializa un objeto Prestamo con los datos especificados.
         * 
         * @param idCuenta ID de la cuenta asociada.
         * @param tipo Tipo de préstamo ('PER', 'PRE', 'HIP').
         * @param moneda Moneda del préstamo ('CRC', 'USD').
         * @param monto Monto solicitado.
         * @param tasaInteres Tasa de interés aplicada.
         * @param plazoMeses Plazo en meses para el pago.
         * @param cuotaMensual Cuota mensual a pagar (opcional, por defecto -1).
         * @param cuotasPagadas Número de cuotas pagadas hasta el momento (opcional, por defecto 0).
         * @param capitalPagado Monto total de capital pagado (opcional, por defecto 0.0).
         * @param interesesPagados Monto total de intereses pagados (opcional, por defecto 0.0).
         * @param activo Estado del préstamo (activo por defecto).
         */
        Prestamo(
            int idCuenta,
            const std::string &tipo,
            const std::string &moneda,
            double monto, 
            double tasaInteres,
            int plazoMeses,
            double cuotaMensual = -1,
            int cuotasPagadas = 0,
            double capitalPagado = 0.0,
            double interesesPagados = 0.0,
            bool activo = true
        );

        /**
         * @brief Crea un registro del préstamo en la base de datos.
         * 
         * Inserta los datos del préstamo en la base de datos.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @return `true` si el registro se crea correctamente, `false` en caso contrario.
         */
        bool crear(sqlite3* db);

        /**
         * @brief Obtiene un préstamo específico de la base de datos.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @param idPrestamo ID del préstamo a obtener.
         * @return Objeto Prestamo con los datos obtenidos.
         */
        static Prestamo obtener(sqlite3* db, int idPrestamo);

        /**
         * @brief Verifica si un préstamo existe en la base de datos.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @param idPrestamo ID del préstamo a verificar.
         * @return `true` si el préstamo existe, `false` en caso contrario.
         */
        static bool existe(sqlite3* db, int idPrestamo);

        /**
         * @brief Calcula la cuota mensual de un préstamo.
         * 
         * @param monto Monto solicitado del préstamo.
         * @param tasaInteres Tasa de interés aplicada.
         * @param plazoMeses Plazo en meses para el pago.
         * @return El monto de la cuota mensual.
         */
        static double calcularCuotaMensual(double monto, double tasaInteres, int plazoMeses);

        /**
         * @brief Realiza un abono a la cuota de un préstamo.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @param cuenta Objeto Cuenta desde la que se realizará el abono.
         * @return `true` si el abono se realiza correctamente, `false` en caso contrario.
         */
        bool abonarCuota(sqlite3* db, Cuenta& cuenta);

        /**
         * @brief Actualiza los datos del préstamo después de un abono.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @return `true` si la actualización es exitosa, `false` en caso contrario.
         */
        bool actualizarDatosAbono(sqlite3* db);

        /**
         * @brief Muestra el historial de abonos del préstamo.
         * 
         * @param db Puntero a la base de datos SQLite.
         */
        void mostrarHistorialAbonos(sqlite3* db) const;

        /**
         * @brief Obtiene el ID del préstamo.
         * 
         * @return El ID del préstamo.
         */
        int getID() const;

        /**
         * @brief Obtiene el ID de la cuenta asociada al préstamo.
         * 
         * @return El ID de la cuenta.
         */
        int getIDCuenta() const;

        /**
         * @brief Establece el ID de la cuenta asociada al préstamo.
         * 
         * @param idCuenta Nuevo ID de la cuenta.
         * @return `true` si el ID se establece correctamente, `false` en caso contrario.
         */
        bool setIDCuenta (int idCuenta);

        /**
         * @brief Muestra la información de pago del préstamo.
         */
        void mostrarInformacionPago() const;

        /**
         * @brief Consulta el estado del préstamo y genera un reporte.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @param idPrestamo ID del préstamo a consultar.
         * @param nombreArchivo Nombre del archivo donde se guardará el reporte (opcional).
         * @return `true` si la consulta es exitosa, `false` en caso contrario.
         */
        static bool consultarEstado(sqlite3* db, int idPrestamo, const std::string& nombreArchivo = "");

        /**
         * @brief Genera un reporte de pago estimado para un préstamo.
         * 
         * @param moneda Moneda del préstamo.
         * @param monto Monto solicitado.
         * @param plazoMeses Plazo en meses.
         * @param tasaInteres Tasa de interés.
         * @param cuotaMensual Cuota mensual calculada.
         */
        static void reportePagoEstimado(const std::string& moneda, double monto, int plazoMeses, double tasaInteres, double cuotaMensual);

        /**
         * @brief Obtiene valores predeterminados para un tipo de préstamo.
         * 
         * @param tipo Tipo de préstamo.
         * @param moneda Moneda del préstamo.
         * @return Estructura ValoresPrestamo con los valores obtenidos.
         */
        static ValoresPrestamo obtenerValoresPredeterminados(TipoPrestamo tipo, const std::string &moneda);
};

#endif // PRESTAMO_HPP
