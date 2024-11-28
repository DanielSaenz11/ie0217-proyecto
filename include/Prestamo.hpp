

#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

#include "Cuenta.hpp"
#include "constants.hpp"
#include <string>
#include <sqlite3.h>

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

        double calcularIntereses();

    public:
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

        bool crear(sqlite3* db);

        static Prestamo obtener(sqlite3* db, int idPrestamo);

        static bool existe(sqlite3* db, int idPrestamo);

        static double calcularCuotaMensual(double monto, double tasaInteres, int plazoMeses);

        bool abonarCuota(sqlite3* db, Cuenta& cuenta);

        bool actualizarDatosAbono(sqlite3* db);

        void mostrarHistorialAbonos(sqlite3* db) const;

        int getID() const;

        int getIDCuenta() const;

        bool setIDCuenta (int idCuenta);

        void mostrarInformacionPago() const;

        static bool consultarEstado(sqlite3* db, int idPrestamo, const std::string& nombreArchivo = "");

        static void reportePagoEstimado(const std::string& moneda, double monto, int plazoMeses, double tasaInteres, double cuotaMensual);

        static ValoresPrestamo obtenerValoresPredeterminados(TipoPrestamo tipo, const std::string &moneda);
};

#endif // PRESTAMO_HPP
