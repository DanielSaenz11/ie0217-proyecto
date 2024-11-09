

#ifndef PAGO_PRESTAMO_HPP
#define PAGO_PRESTAMO_HPP

#include <sqlite3.h>

class PagoPrestamo {
    private:
        int idPrestamo;
        double cuotaPagada;
        double aporteCapital;
        double aporteIntereses;
        double saldoRestante;

    public:
        PagoPrestamo(int idPrestamo, double cuotaPagada);

        bool crear(sqlite3* db);

    private:
        bool calcularAporteCapitalIntereses(sqlite3* db);

        bool actualizarSaldoRestante(sqlite3* db);
        
        bool registrar(sqlite3* db);
};

#endif // PAGO_PRESTAMO_HPP
