

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <sqlite3.h>

class Cliente {
    private:
        int idCliente;
        int cedula;
        std::string nombre;
        std::string primerApellido;
        std::string segundoApellido;
        std::string telefono;

    public:
        // Constructor
        Cliente(int cedula, const std::string &nombre, const std::string &primerApellido, const std::string &segundoApellido, const std::string &telefono);
  
        bool crear(sqlite3* db);

        static Cliente obtener(sqlite3* db, int cedula);

        static bool existe(sqlite3* db, int cedula);

};

#endif // CLIENTE_HPP