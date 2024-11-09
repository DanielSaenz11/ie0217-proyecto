

#include "Cuenta.hpp"
#include "Transaccion.hpp"
#include <iostream>

// Definición del constructor
Cuenta::Cuenta(int idCliente, const std::string &moneda, double saldo, double tasaInteres)
    : idCliente(idCliente), moneda(moneda), saldo(saldo), tasaInteres(tasaInteres) {}

// Definición de función para crear una cuenta bancaria en la base de datos
bool Cuenta::crear(sqlite3* db) {
    // Verifica si ya existe una cuenta en la misma moneda para el cliente
    if (this->existeSegunMoneda(db)) {
        std::cerr << "Error: Ya existe una cuenta con la moneda ingresada." << std::endl;
        return false;
    }

    // Prepara la consulta SQL para insertar una nueva cuenta
    std::string sql = "INSERT INTO Cuentas (idCliente, moneda, saldo, tasaInteres) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    // Verifica si la consulta se preparó correctamente
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Libera la memoria del statement
        return false; // Salir
    }

    // Asigna los valores de la cuenta a la consulta preparada
    sqlite3_bind_int(stmt, 1, idCliente);
    sqlite3_bind_text(stmt, 2, moneda.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, saldo);
    sqlite3_bind_double(stmt, 4, tasaInteres);

    // Ejecuta la consulta y verifica si fue exitosa
    bool exito = sqlite3_step(stmt) == SQLITE_DONE;

    if (exito) {
        // Obtiene el ID de la cuenta creada y lo muestra en pantalla
        idCuenta = sqlite3_last_insert_rowid(db);
        std::cout << "Cuenta creada con ID: " << idCuenta << std::endl;
    } else {
        std::cerr << "Error al insertar en la base de datos: " << sqlite3_errmsg(db) << std::endl;
    }

    // Libera el statement
    sqlite3_finalize(stmt);
    return exito;
}

// Definición de función para buscar una cuenta bancaria según su identificador
Cuenta Cuenta::obtener(sqlite3* db, int idCuenta) {
    // Prepara la consulta SQL para obtener una cuenta por ID
    std::string sql = "SELECT idCliente, moneda, saldo, tasaInteres FROM Cuentas WHERE idCuenta = ?;";
    sqlite3_stmt* stmt;
    
    // Inicializa una cuenta vacía en caso de que la consulta falle
    Cuenta cuenta(0, "", 0.0, 0.0); 

    // Prepara la consulta SQL
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return cuenta;
    }

    // Asigna el ID de la cuenta a buscar en la consulta
    sqlite3_bind_int(stmt, 1, idCuenta);

    // Ejecuta la consulta y verifica si se encuentra la cuenta
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Asigna los valores obtenidos de la consulta a la instancia de cuenta
        cuenta.idCuenta = idCuenta;
        cuenta.idCliente = sqlite3_column_int(stmt, 0);
        cuenta.moneda = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cuenta.saldo = sqlite3_column_double(stmt, 2);
        cuenta.tasaInteres = sqlite3_column_double(stmt, 3);
    } else {
        std::cerr << "Cuenta no encontrada." << std::endl;
    }

    // Libera el statement y retorna la cuenta
    sqlite3_finalize(stmt);
    return cuenta;
}

// Definición de función que verifica la existencia de la cuenta
bool Cuenta::existe(sqlite3* db, int idCuenta) {
    // Prepara la consulta SQL para verificar la existencia de la cuenta
    const std::string sql = "SELECT COUNT(1) FROM Cuentas WHERE idCuenta = ?;";
    sqlite3_stmt* stmt;

    bool existe = false; // Condición de existencia

    // Prepara la consulta y verifica si es válida
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ocurrió un error al preparar la consulta para Cuenta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Libera la memoria del statement
        return false; // Salir
    }

    // Asigna el ID de la cuenta a verificar
    sqlite3_bind_int(stmt, 1, idCuenta);

    // Ejecuta la consulta y verifica si existe la cuenta
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0);
    }

    // Libera el statement
    sqlite3_finalize(stmt);
    return existe;
}


bool Cuenta::actualizarSaldo(sqlite3* db) {
    // Prepara la consulta SQL para actualizar el saldo
    const char* sql = "UPDATE Cuentas SET saldo = ? WHERE idCuenta = ?;";
    sqlite3_stmt* stmt;

    // Prepara la consulta y verifica si es válida
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la actualización de saldo: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Asigna el nuevo saldo y el ID de la cuenta a actualizar
    sqlite3_bind_double(stmt, 1, saldo);
    sqlite3_bind_int(stmt, 2, idCuenta);

    // Ejecuta la actualización y verifica el éxito
    bool exito = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);

    // Si ocurrió un error
    if (!exito) {
        std::cerr << "Error al actualizar el saldo en la base de datos para la cuenta " << idCuenta << std::endl;
    }

    return exito; // Estado de la actualización de saldo
}

// Función para verificar si ya existe una cuenta para el cliente en la moneda especificada
bool Cuenta::existeSegunMoneda(sqlite3* db) {
    // Prepara la consulta SQL para verificar si el cliente tiene otra cuenta en la misma moneda
    std::string checkSQL = "SELECT COUNT(*) FROM Cuentas WHERE idCliente = ? AND moneda = ?;";
    sqlite3_stmt* stmt;

    // Prepara la consulta y verifica si es válida
    if (sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de verificación: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Asigna el ID del cliente y la moneda a verificar
    sqlite3_bind_int(stmt, 1, idCliente);
    sqlite3_bind_text(stmt, 2, moneda.c_str(), -1, SQLITE_STATIC);

    bool existe = false;

    // Ejecuta la consulta y verifica si existe una cuenta en la misma moneda
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }

    // Libera el statement
    sqlite3_finalize(stmt);
    return existe;
}

// Método para ver el saldo de la cuenta
double Cuenta::verSaldo() const {
    return saldo;
}

// Método para obtener el ID de la cuenta
int Cuenta::getID() const {
    return idCuenta;
}

// Método para obtener el ID del cliente de la cuenta
int Cuenta::getIDCliente() const {
    return idCliente;
}


// Método para realizar un depósito a la cuenta
bool Cuenta::depositar(sqlite3* db, double monto) {
    
    // Aumentar saldo con el monto
    saldo += monto;

    // Actualizar el saldo en la base de datos
    if (!actualizarSaldo(db)) {
        saldo -= monto;  // Revertir saldo
        return false; // Salir
    }

    // Hacer transacción de depósito
    if (!crearTransaccion(db, -1, idCuenta, "DEP", monto)) {
        saldo -= monto;  // Revertir el saldo si falla
        std::cerr << "Error: No se pudo procesar el depósito. Fondos revertidos." << std::endl;
        return false;
    }

    return true;
}

// Método para retirar fondos de la cuenta
bool Cuenta::retirar(sqlite3* db, double monto) {
    // Comprobar que existen fondos suficientes
    if (!verificarFondos(monto)) {
        std::cerr << "Error: Fondos insuficientes para retiro." << std::endl;
        return false; // Salir de la función
    }

    saldo -= monto; // Reducir la cantidad de fondos

    // Actualizar el saldo en la base de datos
    if (!actualizarSaldo(db)) {
        saldo += monto;  // Revertir saldo
        return false; // Salir
    }

    // Hacer transaccion de retiro
    if (!crearTransaccion(db, idCuenta, -1, "RET", monto)) {
        saldo += monto;  // Revertir el saldo si falla
        std::cerr << "Error: No se pudo procesar el retiro. Fondos revertidos." << std::endl;
        return false;
    }

    return true;
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
        return false; // Salir
    }

    // Obtener la cuenta de destino y verificar su existencia
    Cuenta cuentaDestino = Cuenta::obtener(db, idCuentaDestino);
    if (cuentaDestino.getID() == 0) {
        std::cerr << "Error: La cuenta destino no existe." << std::endl;
        return false; // Salir
    }

    // Reducir el saldo en la cuenta de origen
    saldo -= monto;

    // Actualizar el saldo en la base de datos para la cuenta de origen
    if (!actualizarSaldo(db)) {
        saldo += monto;  // Revertir saldo en la cuenta de origen
        return false; // Salir
    }

    // Aumentar el saldo en la cuenta de destino
    cuentaDestino.saldo += monto;

     // Actualizar el saldo en la base de datos para la cuenta de destino
    if (!cuentaDestino.actualizarSaldo(db)) {
        saldo += monto;  // Revertir saldo en la cuenta de origen
        actualizarSaldo(db);  // Revertir en la base de datos para cuenta de origen

        cuentaDestino.saldo -= monto;  // Revertir saldo en la cuenta de destino
        return false;
    }

    // Registrar la transacción solo después de que ambos saldos hayan sido actualizados correctamente
    if (!crearTransaccion(db, idCuenta, idCuentaDestino, "TRA", monto)) {
        // Revertir ambos saldos si la transacción falla
        saldo += monto;
        actualizarSaldo(db);

        cuentaDestino.saldo -= monto;
        cuentaDestino.actualizarSaldo(db);

        std::cerr << "Error: No se pudo registrar la transacción de transferencia. Fondos revertidos." << std::endl;
        return false;
    }

    return true;
}


// Método para verificar la compatibilidad de moneda para transferencias entre cuentas
bool Cuenta::verificarCompatibilidadMoneda(sqlite3* db, int idCuentaDestino) const {
    // Prepara la consulta SQL para verificar si el cliente tiene otra cuenta en la misma moneda
    std::string checkSQL = "SELECT COUNT(*) FROM Cuentas WHERE idCuenta = ? AND moneda = ?;";
    sqlite3_stmt* stmt;

    // Prepara la consulta y verifica si es válida
    if (sqlite3_prepare_v2(db, checkSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de verificación: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Liberar la memoria del stmt
        return false; // Salir
    }

    // Asigna el ID del cliente y la moneda a verificar
    sqlite3_bind_int(stmt, 1, idCuentaDestino);
    sqlite3_bind_text(stmt, 2, moneda.c_str(), -1, SQLITE_STATIC);

    bool existe = false;

    // Ejecuta la consulta y verifica si existe una cuenta en la misma moneda
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }

    // Libera el statement
    sqlite3_finalize(stmt);
    return existe;
}

// Método para verificar si hay fondos suficientes para extrar un monto de la cuenta
bool Cuenta::verificarFondos(double monto) const {
    return saldo >= monto;
}


// Método para crear una transacción a partir de un movimiento ingresado
bool Cuenta::crearTransaccion(sqlite3* db, int idRemitente, int idDestinatario, const std::string& tipo, double monto) {
    // Crea una nueva instancia de Transaccion con los detalles
    Transaccion transaccion(idRemitente, idDestinatario, tipo, monto);
    
    // Procesa la transacción y retorna el resultado
    return transaccion.procesar(db);
}


// Método para consultar el historial de movimientos de la cuenta
void Cuenta::consultarHistorial(sqlite3* db) const {
    // Prepara la consulta SQL para obtener el historial de transacciones
    const char* sql = "SELECT * FROM Transacciones WHERE idRemitente = ? OR idDestinatario = ?;";
    sqlite3_stmt* stmt;

    // Prepara la consulta de historial y verifica si es válida
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de historial de transacciones: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Libera el statement
        return; // Salir
    }

    // Asigna el ID de la cuenta para obtener el historial correspondiente
    sqlite3_bind_int(stmt, 1, idCuenta);
    sqlite3_bind_int(stmt, 2, idCuenta);
    
    std::cout << "----- Historial de transacciones de la cuenta -----" << std::endl;
    
    // Itera sobre los resultados de la consulta y muestra cada transacción
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Obtiene los detalles de cada transacción
        int idTransaccion = sqlite3_column_int(stmt, 0);
        int remitente = sqlite3_column_int(stmt, 1);
        int destinatario = sqlite3_column_int(stmt, 2);
        const char* tipo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        double monto = sqlite3_column_double(stmt, 4);
        
        // Imprime los detalles de la transacción en la consola
        std::cout << "ID: " << idTransaccion << " Remitente: " << remitente
                  << " Destinatario: " << destinatario << " Tipo: " << tipo
                  << " Monto: " << monto << std::endl;
    }

    // Libera el statement
    sqlite3_finalize(stmt);
}