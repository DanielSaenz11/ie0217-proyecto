

#ifndef PAGOPRESTAMO_HPP
#define PAGOPRESTAMO_HPP

#include <sqlite3.h>
#include <string>

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
        PagoPrestamo(int idPrestamo, double cuotaPagada, double aporteCapital, double aporteIntereses, double saldoRestante);

        bool crear(sqlite3* db);
};

#endif // PAGO_PRESTAMO_HPP
