

#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

#include <string>
#include <sqlite3.h>

class Prestamo {
    private:
        int idPrestamo;
        int idCuenta;
        std::string tipo;
        double monto;
        double tasaInteres;
        int plazoMeses;
        double cuotaMensual;
        double capitalPagado;
        double interesesPagados;
        double saldoRestante;
        bool activo;
        
        double calcularCuotaMensual(double monto, double tasaInteres, int plazoMeses);

        // Pendiente demás cálculos

    public:
        Prestamo(int idCuenta, const std::string &tipo, double monto, double tasaInteres, int plazoMeses);

        bool crear(sqlite3* db);

        static Prestamo obtener(sqlite3* db, int idPrestamo);

        static bool existe(sqlite3* db, int idPrestamo);
};

#endif // PRESTAMO_HPP
