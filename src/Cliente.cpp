

#include "Cliente.hpp"
#include <iostream>

Cliente::Cliente(int cedula, const std::string &nombre, const std::string &primerApellido, const std::string &segundoApellido, const std::string &telefono)
    : cedula(cedula), nombre(nombre), primerApellido(primerApellido), segundoApellido(segundoApellido), telefono(telefono) {}


bool Cliente::crear(sqlite3* db) {

    // Verificar que no existe un cliente con ese número de cédula
    if (Cliente::existe(db, this->cedula)) {
        std::cout << "Error: Ya existe un cliente con el número de cédula" << std::endl;
        return false; // Salir de la función
    }

    // Consulta para la inserción a la base de datos db
    std::string sql = "INSERT INTO Clientes (cedula, nombre, primerApellido, segundoApellido, telefono) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt; // Declaración de statement

    // Preparar la consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Ingreso de valores a insertar al stmt con sqlite3_bind_int
    sqlite3_bind_int(stmt, 1, cedula);
    sqlite3_bind_text(stmt, 2, nombre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, primerApellido.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, segundoApellido.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, telefono.c_str(), -1, SQLITE_STATIC);

    // Insertar en la base de datos db
    bool exito = (sqlite3_step(stmt) == SQLITE_DONE);

    if (exito) {
        idCliente = sqlite3_last_insert_rowid(db);
        std::cout << "Cliente creado con ID: " << idCliente << std::endl;
    } else {
        std::cerr << "Error al insertar en la base de datos: " << sqlite3_errmsg(db) << std::endl;
    }
    
    // Retornar estado de inserción
    return exito;
}


Cliente Cliente::obtener(sqlite3* db, int cedula) {
    // Consulta para seleccionar datos de Cliente a partir de su cedula
    std::string sql = "SELECT nombre, primerApellido, segundoApellido, telefono FROM Clientes WHERE cedula = ?;";
    
    // Declaración de statement
    sqlite3_stmt* stmt;


    Cliente cliente(0, "", "", "", "");
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return cliente;
    }
    sqlite3_bind_int(stmt, 1, cedula);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cliente.cedula = cedula;
        cliente.nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        cliente.primerApellido = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cliente.segundoApellido = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        cliente.telefono = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    }
    else {
        std::cerr << "Cliente no encontrado." << std::endl;
    }

    sqlite3_finalize(stmt);
    
    return cliente;
}

bool Cliente::existe(sqlite3* db, int cedula) {
    // Plantilla de la consulta que recibe un parámetro que será el idCliente que se proveee como parámetro
    const std::string sql = "SELECT COUNT(1) FROM Clientes WHERE cedula = ?;";
    sqlite3_stmt* stmt;
    bool exists = false;

    // Verifica si sucede un error al preparar la consulta. Se imprime este mensaje de error
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ocurrió un error al preparar la consulta para Cliente: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    /*
    Se utiliza la función 'sqlite3_bind_int' para pasarle a la consulta previamente declarada el
    parámetro idCliente para realizar la verificación
    */
    sqlite3_bind_int(stmt, 1, cedula);

    /*
    Por medio de la función 'sqlite3_step' se ejecuta la consulta con la configuración que se estableció 
    previamente, y retorna el numero de registros que coinciden con la consulta y asigna este valor a exists
    */
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    // Destructor del 'stmt' para liberar su memoria ocupada
    sqlite3_finalize(stmt);
    return exists;
}
