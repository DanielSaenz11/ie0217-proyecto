

#ifndef TRANSACCION_HPP
#define TRANSACCION_HPP

#include <string>
#include <sqlite3.h>

class Transaccion {
    private:
        int idRemitente;
        int idDestinatario;
        std::string tipo;
        double monto;

    public:
        Transaccion(int idRemitente, int idDestinatario, const std::string &tipo, double monto);

        bool procesar(sqlite3* db);
};

#endif // TRANSACCION_HPP
