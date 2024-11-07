

#ifndef CDP_HPP
#define CDP_HPP

#include <string>
#include <sqlite3.h>

class CDP {
    private:
        int idCDP;
        int idCuenta;
        double deposito;
        int plazoMeses;
        double tasaInteres;
        std::string fechaSolicitud;

    public:
        CDP(int idCuenta, double deposito, int plazoMeses, double tasaInteres, const std::string &fechaSolicitud);

        bool crear(sqlite3* db);

        static CDP obtener(sqlite3* db, int idCDP);
};

#endif // CDP_HPP
