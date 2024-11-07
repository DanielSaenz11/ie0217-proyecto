

#ifndef CUENTA_HPP
#define CUENTA_HPP

#include <string>
#include <sqlite3.h>

class Cuenta {
    private:
        int idCuenta;
        int idCliente;
        std::string moneda;
        double saldo;
        double tasaInteres;

        bool existeSegunMoneda(sqlite3* db);

        bool verificarFondos(double monto) const;

        bool crearTransaccion(sqlite3* db, int idRemitente, int idDestinatario, const std::string& tipo, double monto);

        bool verificarCompatibilidadMoneda(sqlite3* db, int idCuentaDestino) const;

    public:
        Cuenta(int idCliente, const std::string &moneda, double saldo, double tasaInteres);

        bool crear(sqlite3* db);

        static Cuenta obtener(sqlite3* db, int idCuenta);

        static bool existe(sqlite3* db, int idCuenta);

        double verSaldo() const;

        bool depositar(sqlite3* db, double monto);

        bool retirar(sqlite3* db, double monto);

        bool transferir(sqlite3* db, int idCuentaDestino, double monto);

        bool abonarPrestamo(sqlite3* db, int idPrestamo, double monto);

        bool solicitarCDP(sqlite3* db, double monto, int plazoMeses);

        void consultarHistorial(sqlite3* db) const; 
};

#endif // CUENTA_HPP
