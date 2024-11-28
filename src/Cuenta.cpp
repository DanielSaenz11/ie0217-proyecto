

#include "Cuenta.hpp"
#include "Transaccion.hpp"
#include "SQLiteStatement.hpp"
#include "CDP.hpp"
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

    // Consulta SQL para insertar una nueva cuenta
    const std::string sql = "INSERT INTO Cuentas (idCliente, moneda, saldo, tasaInteres) VALUES (?, ?, ?, ?);";

    try {
        // Utiliza SQLiteStatement para manejar el ciclo de vida del statement
        SQLiteStatement statement(db, sql);

        // Asigna los valores de la cuenta a la consulta preparada
        sqlite3_bind_int(statement.get(), 1, idCliente);
        sqlite3_bind_text(statement.get(), 2, moneda.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(statement.get(), 3, saldo);
        sqlite3_bind_double(statement.get(), 4, tasaInteres);

        // Ejecuta la consulta y verifica si fue exitosa
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error: No se pudo insertar en la base de datos.");
        }

        // Obtiene el ID de la cuenta creada
        idCuenta = sqlite3_last_insert_rowid(db);
        std::cout << "Cuenta creada con ID: " << idCuenta << std::endl;

        return true;

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
        return false;
    }
}

// Definición de función para buscar una cuenta bancaria según su identificador
Cuenta Cuenta::obtener(sqlite3* db, int idCuenta) {
    // Prepara la consulta SQL para obtener una cuenta por ID
    std::string sql = "SELECT idCliente, moneda, saldo, tasaInteres FROM Cuentas WHERE idCuenta = ?;";
    
    // Inicializa una cuenta vacía en caso de que la consulta falle
    Cuenta cuenta(0, "", 0.0, 0.0); 

    try {
        SQLiteStatement statement(db, sql);

        // Asigna el ID de la cuenta a buscar en la consulta
        sqlite3_bind_int(statement.get(), 1, idCuenta);

        // Ejecuta la consulta y verifica si se encuentra la cuenta
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Asigna los valores obtenidos de la consulta a la instancia de cuenta
            cuenta.idCuenta = idCuenta;
            cuenta.idCliente = sqlite3_column_int(statement.get(), 0);
            cuenta.moneda = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 1));
            cuenta.saldo = sqlite3_column_double(statement.get(), 2);
            cuenta.tasaInteres = sqlite3_column_double(statement.get(), 3);
        } else {
            throw std::runtime_error("Error: Cuenta no encontrada.");
        }
    } catch (const std::exception& e) {
        // Maneja errores y reporta mensajes en consola
        std::cerr << e.what() << std::endl;
    }
    
    return cuenta;
}

// Definición de función que verifica la existencia de la cuenta
bool Cuenta::existe(sqlite3* db, int idCuenta) {
    // Consulta SQL para verificar la existencia de la cuenta
    const std::string sql = "SELECT COUNT(1) FROM Cuentas WHERE idCuenta = ?;";

    try {
        SQLiteStatement statement(db, sql);

        // Asigna el ID de la cuenta a verificar
        sqlite3_bind_int(statement.get(), 1, idCuenta);

        // Ejecuta la consulta y verifica si existe la cuenta
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            return sqlite3_column_int(statement.get(), 0) > 0;
        } else {
            throw std::runtime_error("Error: No se pudo ejecutar la consulta.");
        }

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
        return false;
    }
}


bool Cuenta::actualizarSaldo(sqlite3* db) {
    // Consulta SQL para actualizar el saldo
    const std::string sql = "UPDATE Cuentas SET saldo = ? WHERE idCuenta = ?;";

    try {
        SQLiteStatement statement(db, sql);

        // Asigna el nuevo saldo y el ID de la cuenta a actualizar
        sqlite3_bind_double(statement.get(), 1, saldo);
        sqlite3_bind_int(statement.get(), 2, idCuenta);

        // Ejecuta la actualización
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error: No se pudo ejecutar la actualización de saldo.");
        }

        // Actualización exitosa
        std::cout << "Saldo actualizado correctamente para la cuenta: " << idCuenta << std::endl;
        return true;

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
        return false;
    }
}

// Función para verificar si ya existe una cuenta para el cliente en la moneda especificada
bool Cuenta::existeSegunMoneda(sqlite3* db) {
    // Consulta SQL para verificar si el cliente tiene otra cuenta en la misma moneda
    const std::string checkSQL = "SELECT COUNT(*) FROM Cuentas WHERE idCliente = ? AND moneda = ?;";

    try {
        SQLiteStatement statement(db, checkSQL);

        // Asigna el ID del cliente y la moneda a verificar
        sqlite3_bind_int(statement.get(), 1, idCliente);
        sqlite3_bind_text(statement.get(), 2, moneda.c_str(), -1, SQLITE_STATIC);

        // Ejecuta la consulta y verifica si existe una cuenta en la misma moneda
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            return sqlite3_column_int(statement.get(), 0) > 0;
        } else {
            throw std::runtime_error("Error: No se pudo ejecutar la consulta.");
        }

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
        return false;
    }
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

std::string Cuenta::getMoneda() const {
    return moneda;
}


// Método para realizar un depósito a la cuenta
bool Cuenta::depositar(sqlite3* db, double monto) {
    try {
        // Comenzar una transacción
        if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error: No se pudo iniciar la transacción.");
        }

        // Aumentar el saldo en la instancia
        saldo += monto;

        // Actualizar el saldo en la base de datos
        if (!actualizarSaldo(db)) {
            saldo -= monto; // Revertir el saldo en la instancia
            throw std::runtime_error("Error: No se pudo actualizar el saldo en la base de datos.");
        }

        // Registrar la transacción como depósito
        if (!crearTransaccion(db, -1, idCuenta, "DEP", monto)) {
            saldo -= monto; // Revertir el saldo en la instancia
            throw std::runtime_error("Error: No se pudo registrar la transacción de depósito.");
        }

        // Confirmar la transacción
        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            saldo -= monto; // Revertir el saldo en la instancia
            throw std::runtime_error("Error: No se pudo confirmar la transacción.");
        }

        return true; // Depósito exitoso

    } catch (const std::exception& e) {
        // Realizar rollback en caso de error
        std::cerr << e.what() << std::endl;
        if (sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, nullptr) != SQLITE_OK) {
            std::cerr << "Error: No se pudo realizar el rollback." << std::endl;
        }
        return false; // Depósito fallido
    }
}


// Método para retirar fondos de la cuenta
bool Cuenta::retirar(sqlite3* db, double monto) {
    try {
        // Comenzar una transacción
        if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error: No se pudo iniciar la transacción.");
        }

        // Verificar si hay fondos suficientes
        if (!verificarFondos(monto)) {
            throw std::runtime_error("Error: Fondos insuficientes para retiro.");
        }

        // Reducir saldo en la instancia
        saldo -= monto;

        // Actualizar el saldo en la base de datos
        if (!actualizarSaldo(db)) {
            saldo += monto; // Revertir el saldo en la instancia
            throw std::runtime_error("Error: No se pudo actualizar el saldo en la base de datos.");
        }

        // Registrar la transacción como retiro
        if (!crearTransaccion(db, idCuenta, -1, "RET", monto)) {
            saldo += monto; // Revertir el saldo en la instancia
            throw std::runtime_error("Error: No se pudo registrar la transacción de retiro.");
        }

        // Confirmar la transacción
        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            saldo += monto; // Revertir el saldo en la instancia
            throw std::runtime_error("Error: No se pudo confirmar la transacción.");
        }

        return true; // Retiro exitoso
        
    } catch (const std::exception& e) {
        // Realizar rollback en caso de error
        std::cerr << e.what() << std::endl;
        if (sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, nullptr) != SQLITE_OK) {
            std::cerr << "Error: No se pudo realizar el rollback." << std::endl;
        }
        return false; // Retiro fallido
    }
}


// Método para transferir fondos desde la instancia de Cuenta a otra
bool Cuenta::transferir(sqlite3* db, int idCuentaDestino, double monto) {
    int saldoOriginal = saldo;
    
    try {
        // Verificar fondos de la cuenta actual
        if (!verificarFondos(monto)) {
            throw std::runtime_error("Error: Fondos insuficientes para transferencia.");
        }

        // Obtener cuenta destino
        Cuenta cuentaDestino = Cuenta::obtener(db, idCuentaDestino);
        if (cuentaDestino.getID() == 0) {
            throw std::runtime_error("Error: No se pudo encontrar la cuenta destino.");
        }

        // Iniciar transacción SQL
        if (sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error: No se pudo iniciar la transacción.");
        }

        // Reducir saldo en la cuenta de origen
        saldo -= monto;
        if (!actualizarSaldo(db)) {
            throw std::runtime_error("Error: No se pudo actualizar el saldo de la cuenta remitente.");
        }

        // Aumentar saldo en la cuenta destino
        cuentaDestino.saldo += monto;
        if (!cuentaDestino.actualizarSaldo(db)) {
            throw std::runtime_error("Error: No se pudo actualizar el saldo de la cuenta destino.");
        }

        // Registrar la transacción
        if (!crearTransaccion(db, idCuenta, idCuentaDestino, "TRA", monto)) {
            throw std::runtime_error("Error: No se pudo registrar la transacción.");
        }

        // Confirmar transacción SQL
        if (sqlite3_exec(db, "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error: No se pudo confirmar la transacción.");
        }

        return true; // Transferencia exitosa

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;

        // Revertir transacción SQL en caso de fallo
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);

        // Revertir saldo en el objeto
        saldo = saldoOriginal;

        return false; // Transferencia fallida
    }
}


// Método para realizar la reducción de saldo al abonar un préstamo
bool Cuenta::abonarPrestamo(sqlite3* db, double monto) {
    try {
        // Verificar si hay suficientes fondos
        if (!verificarFondos(monto)) {
            throw std::runtime_error("Error: Fondos insuficientes para realizar el abono.");
        }

        // Reducir el saldo en memoria
        saldo -= monto;

        // Registrar la transacción de tipo "ABO"
        Transaccion transaccion(idCuenta, -1, "ABO", monto);
        if (!transaccion.procesar(db)) {
            saldo += monto; // Revertir el saldo
            throw std::runtime_error("Error: No se pudo procesar la transacción de abono.");
        }

        // Actualizar el saldo en la base de datos
        const std::string sql = "UPDATE Cuentas SET saldo = ? WHERE idCuenta = ?;";
        SQLiteStatement statement(db, sql);

        sqlite3_bind_double(statement.get(), 1, saldo);
        sqlite3_bind_int(statement.get(), 2, idCuenta);

        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            saldo += monto; // Revertir el saldo en memoria
            throw std::runtime_error("Error: No se pudo actualizar el saldo en la base de datos.");
        }

        return true; // Abono exitoso

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;

        return false; // Abono fallido
    }
}


// Método para solicitar un CDP
bool Cuenta::solicitarCDP(sqlite3* db, std::string &moneda, double monto, int plazoMeses, double tasaInteres) {
    try {
        // Iniciar transacción
        if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error: No se pudo iniciar la transacción.");
        }

        // Verificar fondos suficientes
        if (!verificarFondos(monto)) {
            throw std::runtime_error("Error: Fondos insuficientes para solicitar el CDP.");
        }

        // Reducir el saldo de la cuenta en el objeto de Cuenta
        saldo -= monto;

        // Actualizar el saldo en la base de datos
        std::string actualizarSaldoSQL = "UPDATE Cuentas SET saldo = ? WHERE idCuenta = ?;";
        {
            // Bloque de código para liberar el statement cuando salga
            SQLiteStatement statement(db, actualizarSaldoSQL);
            sqlite3_bind_double(statement.get(), 1, saldo);
            sqlite3_bind_int(statement.get(), 2, idCuenta);

            if (sqlite3_step(statement.get()) != SQLITE_DONE) {
                saldo += monto; // Reintegrar los fondos al saldo de la cuenta
                throw std::runtime_error("Error: No se pudo actualizar el saldo en la base de datos.");
            }
        }

        // Crear el CDP en la base de datos
        CDP cdp(idCuenta, moneda, monto, plazoMeses, tasaInteres);
        if (!cdp.crear(db)) {
            saldo += monto; // Reintegrar los fondos al saldo de la cuenta
            throw std::runtime_error("Error: No se pudo crear el CDP en la base de datos.");
        }

        // Registrar la transacción del CDP
        Transaccion transaccion(idCuenta, -1, "CDP", monto);
        if (!transaccion.procesar(db)) {
            saldo += monto; // Reintegrar los fondos al saldo de la cuenta
            throw std::runtime_error("Error: No se pudo registrar la transacción del CDP.");
        }

        // Confirmar transacción
        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            saldo += monto; // Reintegrar los fondos al saldo de la cuenta
            throw std::runtime_error("Error: No se pudo confirmar la transacción.");
        }
        
        return true; // Abono exitoso

    } catch (const std::exception& e) {
        // Realizar rollback en caso de error
        std::cerr << e.what() << std::endl;
        if (sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, nullptr) != SQLITE_OK) {
            std::cerr << "Error: No se pudo realizar el rollback." << std::endl;
        }

        return false; // Abono fallido
    }
}


// Método para verificar la compatibilidad de moneda para transferencias entre cuentas
bool Cuenta::verificarCompatibilidadMoneda(sqlite3* db, int idCuentaDestino) const {
    // Consulta SQL para verificar si la cuenta destino tiene la misma moneda
    const std::string checkSQL = "SELECT COUNT(*) FROM Cuentas WHERE idCuenta = ? AND moneda = ?;";

    try {
        SQLiteStatement statement(db, checkSQL);

        // Asigna el ID de la cuenta destino y la moneda a verificar
        sqlite3_bind_int(statement.get(), 1, idCuentaDestino);
        sqlite3_bind_text(statement.get(), 2, moneda.c_str(), -1, SQLITE_STATIC);

        // Ejecuta la consulta y verifica si existe compatibilidad de moneda
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            return sqlite3_column_int(statement.get(), 0) > 0;
        } else {
            throw std::runtime_error("Error: No se pudo ejecutar la consulta.");
        }

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
        return false;
    }
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
    // Consulta SQL para obtener el historial de transacciones
    const std::string sql = "SELECT * FROM Transacciones WHERE idRemitente = ? OR idDestinatario = ?;";

    try {
        // Utiliza SQLiteStatement para manejar el ciclo de vida del statement
        SQLiteStatement statement(db, sql);

        // Asigna el ID de la cuenta para obtener el historial correspondiente
        sqlite3_bind_int(statement.get(), 1, idCuenta);
        sqlite3_bind_int(statement.get(), 2, idCuenta);

        std::cout << "----- Historial de transacciones de la cuenta -----" << std::endl;

        // Itera sobre los resultados de la consulta y muestra cada transacción
        while (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Obtiene los detalles de cada transacción
            int idTransaccion = sqlite3_column_int(statement.get(), 0);
            int remitente = sqlite3_column_int(statement.get(), 1);
            int destinatario = sqlite3_column_int(statement.get(), 2);
            const char* tipo = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 3));
            double monto = sqlite3_column_double(statement.get(), 4);

            // Imprime los detalles de la transacción en la consola
            std::cout << "ID: " << idTransaccion << " Remitente: " << remitente
                      << " Destinatario: " << destinatario << " Tipo: " << tipo
                      << " Monto: " << monto << std::endl;
        }

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
    }
}