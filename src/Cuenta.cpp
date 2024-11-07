

#include "Cuenta.hpp"
#include "Transaccion.hpp"
#include <iostream>

// Definición del constructor
Cuenta::Cuenta(int idCliente, const std::string &moneda, double saldo, double tasaInteres)
    : idCliente(idCliente), moneda(moneda), saldo(saldo), tasaInteres(tasaInteres) {}

// Definición de función para crear una cuenta bancaria
bool Cuenta::crear(sqlite3* db) {
    if (this->existeSegunMoneda(db)) {
        return false;
    }

    std::string sql = "INSERT INTO Cuentas (idCliente, moneda, saldo, tasaInteres) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Insertar los valores de la cuenta a crear dentro del statement
    sqlite3_bind_int(stmt, 1, idCliente);
    sqlite3_bind_text(stmt, 2, moneda.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, saldo);
    sqlite3_bind_double(stmt, 4, tasaInteres);


    bool exito = sqlite3_step(stmt) == SQLITE_DONE;

     if (exito) {
        idCuenta = sqlite3_last_insert_rowid(db);
        std::cout << "Cuenta creada con ID: " << idCuenta << std::endl;
    } else {
        std::cerr << "Error al insertar en la base de datos: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return exito;
}

// Definición de función para buscar una cuenta bancaria según su identificador
Cuenta Cuenta::obtener(sqlite3* db, int idCuenta) {
    std::string sql = "SELECT idCliente, moneda, saldo, tasaInteres FROM Cuentas WHERE idCuenta = ?;";
    sqlite3_stmt* stmt;

    Cuenta cuenta(0, "", 0.0, 0.0);

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return cuenta; // Retorna cuenta vacía
    }

    sqlite3_bind_int(stmt, 1, idCuenta);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cuenta.idCliente = sqlite3_column_int(stmt, 0);
        cuenta.moneda = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cuenta.saldo = sqlite3_column_double(stmt, 2);
        cuenta.tasaInteres = sqlite3_column_double(stmt, 3);
    }
    else {
        std::cerr << "Cuenta no encontrada." << std::endl;
    }

    sqlite3_finalize(stmt);
    return cuenta;
}

// Definición de función que verifica la existencia de la cuenta
bool Cuenta::existe(sqlite3* db, int idCuenta) {
    const std::string sql = "SELECT COUNT(1) FROM Cuentas WHERE idCuenta = ?;";
    
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ocurrió un error al preparar la consulta para Cuenta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idCuenta);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists;
}


// Función para verificar si ya existe una cuenta para el cliente en la moneda especificada
bool Cuenta::existeSegunMoneda(sqlite3* db) {
    std::string checkSQL = "SELECT COUNT(*) FROM Cuentas WHERE idCliente = ? AND moneda = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de verificación: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Ingresar idCliente y moneda al statement para la consulta
    sqlite3_bind_int(stmt, 1, idCliente);
    sqlite3_bind_text(stmt, 2, moneda.c_str(), -1, SQLITE_STATIC);

    bool exists = false; // Variable booleana para la condición de existencia

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0; // Contador mayor a 0
    }

    sqlite3_finalize(stmt);

    return exists;
}


// Método para ver el saldo de la cuenta
double Cuenta::verSaldo() const {
    return saldo;
}

// Método para realizar un depósito a la cuenta
bool Cuenta::depositar(sqlite3* db, double monto) {
    
    // Aumentar saldo con el monto
    saldo += monto;

    // Hacer transacción de depósito
    return crearTransaccion(db, -1, idCuenta, "DEP", monto);
}

// Método para retirar fondos de la cuenta
bool Cuenta::retirar(sqlite3* db, double monto) {
    // Comprobar que existen fondos suficientes
    if (!verificarFondos(monto)) {
        std::cerr << "Error: Fondos insuficientes para retiro." << std::endl;
        return false; // Salir de la función
    }

    saldo -= monto; // Reducir la cantidad de fondos

    // Hacer transaccion de retiro
    return crearTransaccion(db, idCuenta, -1, "RET", monto);
}

// Método para transferir fondos desde la instancia de Cuenta a otra
bool Cuenta::transferir(sqlite3* db, int idCuentaDestino, double monto) {
    // Verificar que existen fondos suficientes en la cuenta del remitente
    if (!verificarFondos(monto)) {
        std::cerr << "Error: Fondos insuficientes para transferencia." << std::endl;
        return false; // Salir
    }

    // Verificación de moneda entre cuentas
    if (!verificarCompatibilidadMoneda(db, idCuentaDestino)) {
        std::cerr << "Error: Las cuentas deben ser de la misma moneda para realizar la transferencia." << std::endl;
        return false;
    }

    // Reducir el saldo por el monto transferido
    saldo -= monto;

    // Hacer la transacción
    return crearTransaccion(db, idCuenta, idCuentaDestino, "TRA", monto);
}


// Método para verificar la compatibilidad de moneda para transferencias entre cuentas
bool Cuenta::verificarCompatibilidadMoneda(sqlite3* db, int idCuentaDestino) const {
    const char* sql = "SELECT moneda FROM Cuentas WHERE idCuenta = ?;";
    
    sqlite3_stmt* stmt;
    
    bool compatible = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar consulta para verificar moneda de la cuenta destino: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, idCuentaDestino);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* monedaDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        compatible = (monedaDestino && moneda == monedaDestino);
    }

    sqlite3_finalize(stmt);

    return compatible;
}

// Método para verificar si hay fondos suficientes para extrar un monto de la cuenta
bool Cuenta::verificarFondos(double monto) const {
    return saldo >= monto;
}


// Método para crear una transacción a partir de un movimiento ingresado
bool Cuenta::crearTransaccion(sqlite3* db, int idRemitente, int idDestinatario, const std::string& tipo, double monto) {
    
    Transaccion transaccion(idRemitente, idDestinatario, tipo, monto);
    
    return transaccion.procesar(db);
}


// Método para consultar el historial de movimientos de la cuenta
void Cuenta::consultarHistorial(sqlite3* db) const {
    const char* sql = "SELECT * FROM Transacciones WHERE idRemitente = ? OR idDestinatario = ?;";
    
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de historial de transacciones: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, idCuenta);
    sqlite3_bind_int(stmt, 2, idCuenta);
    
    std::cout << "----- Historial de transacciones de la cuenta -----" << std::endl;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int idTransaccion = sqlite3_column_int(stmt, 0);
        int remitente = sqlite3_column_int(stmt, 1);
        int destinatario = sqlite3_column_int(stmt, 2);
        const char* tipo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        double monto = sqlite3_column_double(stmt, 4);
        
        std::cout << "ID: " << idTransaccion << " Remitente: " << remitente
                  << " Destinatario: " << destinatario << " Tipo: " << tipo
                  << " Monto: " << monto << std::endl;
    }

    sqlite3_finalize(stmt);
}