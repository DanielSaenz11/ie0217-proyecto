/**
 * @file inicio_db.cpp
 * @brief Implementación de inicio de una base de datos SQLite de clientes bancarios.
 * @details Este archivo contiene funciones para crear las tablas necesarias en la base de datos,
 *          insertar datos de ejemplo y realizar operaciones SQL en una base de datos de un banco.
 *          Utiliza la biblioteca SQLite3 para interactuar con la base de datos "banco.db".
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#include <iostream>
#include <sqlite3.h>

/// @brief Nombre de la base de datos utilizada en este programa.
const char* DB_NAME = "banco.db";

/**
 * @brief Script SQL para la creación de las tablas en la base de datos.
 * 
 * Este script incluye la creación de las tablas Clientes, Cuentas, CDP, Transacciones, Prestamos,
 * y PagoPrestamos, al asegurar las restricciones necesarias en cada campo para la integridad de los datos.
 */
const char* SQL_CREATE_TABLES = R"(
    CREATE TABLE IF NOT EXISTS Clientes (
        idCliente INTEGER PRIMARY KEY AUTOINCREMENT CHECK (idCliente <= 999999999),
        cedula INTEGER UNIQUE NOT NULL,
        nombre TEXT NOT NULL,
        primerApellido TEXT NOT NULL,
        segundoApellido TEXT,
        telefono TEXT
    );

    CREATE INDEX IF NOT EXISTS idx_cedula_clientes ON Clientes(cedula);

    CREATE TABLE IF NOT EXISTS Cuentas (
        idCuenta INTEGER PRIMARY KEY AUTOINCREMENT,
        idCliente INTEGER NOT NULL,
        moneda TEXT NOT NULL CHECK (moneda IN ('CRC', 'USD')),
        saldo REAL NOT NULL,
        tasaInteres REAL NOT NULL,
        FOREIGN KEY (idCliente) REFERENCES Clientes(idCliente)
    );

    CREATE INDEX IF NOT EXISTS idx_idCuenta_cuentas ON Cuentas(idCuenta);
    CREATE INDEX IF NOT EXISTS idx_idCliente_cuentas ON Cuentas(idCliente);

    CREATE TABLE IF NOT EXISTS CDP (
        idCDP INTEGER PRIMARY KEY AUTOINCREMENT,
        idCuenta INTEGER NOT NULL,
        moneda TEXT NOT NULL CHECK (moneda IN ('CRC', 'USD')),
        deposito REAL NOT NULL,
        plazoMeses INTEGER NOT NULL,
        tasaInteres REAL NOT NULL,
        FOREIGN KEY (idCuenta) REFERENCES Cuentas(idCuenta)
    );

    CREATE INDEX IF NOT EXISTS idx_idCuenta_cdp ON CDP(idCuenta);

    CREATE TABLE IF NOT EXISTS Transacciones (
        idTransaccion INTEGER PRIMARY KEY AUTOINCREMENT,
        idRemitente INTEGER,
        idDestinatario INTEGER,
        tipo TEXT NOT NULL CHECK (tipo IN ('DEP', 'RET', 'TRA', 'ABO', 'CDP')),
        monto REAL NOT NULL,
        FOREIGN KEY (idRemitente) REFERENCES Cuentas(idCuenta),
        FOREIGN KEY (idDestinatario) REFERENCES Cuentas(idCuenta)
    );

    CREATE INDEX IF NOT EXISTS idx_idRemitente_transacciones ON Transacciones(idRemitente);
    CREATE INDEX IF NOT EXISTS idx_idDestinatario_transacciones ON Transacciones(idDestinatario);

    CREATE TABLE IF NOT EXISTS Prestamos (
        idPrestamo INTEGER PRIMARY KEY AUTOINCREMENT,
        idCuenta INTEGER NOT NULL,
        tipo TEXT NOT NULL CHECK (tipo IN ('PER', 'PRE', 'HIP')),
        moneda TEXT NOT NULL CHECK (moneda IN ('CRC', 'USD')),
        monto REAL NOT NULL,
        tasaInteres REAL NOT NULL,
        plazoMeses INTEGER NOT NULL,
        cuotaMensual REAL NOT NULL,
        cuotasPagadas INTEGER NOT NULL DEFAULT 0,
        capitalPagado REAL NOT NULL DEFAULT 0,
        interesesPagados REAL NOT NULL DEFAULT 0,
        activo BOOLEAN NOT NULL DEFAULT 1,
        FOREIGN KEY (idCuenta) REFERENCES Cuentas(idCuenta)
    );

    CREATE INDEX IF NOT EXISTS idx_idCuenta_prestamos ON Prestamos(idCuenta);
    CREATE INDEX IF NOT EXISTS idx_idPrestamo_prestamos ON Prestamos(idPrestamo);

    CREATE TABLE IF NOT EXISTS PagoPrestamos (
        idPagoPrestamo INTEGER PRIMARY KEY AUTOINCREMENT,
        idPrestamo INTEGER NOT NULL,
        cuotaPagada REAL NOT NULL,
        aporteCapital REAL NOT NULL,
        aporteIntereses REAL NOT NULL,
        saldoRestante REAL NOT NULL,
        FOREIGN KEY (idPrestamo) REFERENCES Prestamos(idPrestamo)
    );
)";


/**
 * @brief Ejecuta un comando SQL en la base de datos.
 * 
 * Esta función intenta ejecutar el comando SQL especificado en la base de datos.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param sql Comando SQL a ejecutar.
 * @return `void`
 */
bool ejecutarSQL(sqlite3* db, const char* sql) {
    // Ejecución de comando SQL
    if (sqlite3_exec(db, sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta SQL." << std::endl;
        return false; // Operación fallida
    }

    return true; // Operación exitosa
}

/**
 * @brief Inserta datos de ejemplo en las tablas de la base de datos.
 * 
 * Esta función inserta datos de ejemplo en las tablas Clientes, Cuentas, CDP, Transacciones,
 * Prestamos y PagoPrestamos, con datos ficticios para representar clientes, cuentas y transacciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @return `void`
 */
void insertarDatos(sqlite3* db) {
    const char* sqlInsertarDatos = R"(
        -- Insertar datos en Clientes
        INSERT INTO Clientes (cedula, nombre, primerApellido, segundoApellido, telefono) VALUES 
        (101010101, 'Juan', 'Perez', 'Garcia', '1234-5678'),
        (202020202, 'Maria', 'Lopez', 'Fernandez', '8765-4321'),
        (303030303, 'Carlos', 'Ramirez', 'Soto', '4567-8901'),
        (404040404, 'Ana', 'Jimenez', 'Mora', '2345-6789');

        -- Insertar datos en Cuentas
        INSERT INTO Cuentas (idCliente, moneda, saldo, tasaInteres) VALUES 
        (1, 'CRC', 150000.0, 2.5),
        (1, 'USD', 500.0, 1.5),
        (2, 'CRC', 200000.0, 2.0),
        (3, 'CRC', 100000.0, 2.0),
        (3, 'USD', 350.0, 1.2),
        (4, 'CRC', 250000.0, 2.7);

        -- Insertar datos en CDP
        INSERT INTO CDP (idCuenta, moneda, deposito, plazoMeses, tasaInteres) VALUES
        (1, 'CRC', 60000.0, 12, 2.5),
        (3, 'CRC', 120000.0, 24, 3.0),
        (5, 'USD', 500.0, 18, 2.8);

        -- Insertar transacciones
        INSERT INTO Transacciones (idRemitente, idDestinatario, tipo, monto) VALUES 
        (1, 2, 'TRA', 25000.0),
        (2, NULL, 'RET', 3000.0),
        (NULL, 1, 'DEP', 12000.0),
        (3, 4, 'TRA', 45000.0),
        (NULL, 1, 'CDP', 1000.0),
        (5, NULL, 'ABO', 250.0);

        -- Insertar préstamos
        INSERT INTO Prestamos (idCuenta, tipo, moneda, monto, tasaInteres, plazoMeses, cuotaMensual, cuotasPagadas, capitalPagado, interesesPagados, activo) VALUES 
        (1, 'PER', 'CRC', 100000.0, 5.0, 24, 5000.0, 2, 10000.0, 2500.0, 1),
        (5, 'HIP', 'USD', 50000.0, 3.5, 120, 1500.0, 3, 3000.0, 750.0, 1);

        -- Insertar datos en PagoPrestamos
        INSERT INTO PagoPrestamos (idPrestamo, cuotaPagada, aporteCapital, aporteIntereses, saldoRestante) VALUES 
        (1, 5000.0, 4000.0, 1000.0, 83500.0),
        (1, 5000.0, 4200.0, 800.0, 79300.0),
        (2, 1500.0, 1200.0, 300.0, 45000.0);
    )";


    // Ejecución del comando de inserción de datos
    if (ejecutarSQL(db, sqlInsertarDatos)) {
       std::cout << "Datos insertados exitosamente en todas las tablas." << std::endl;
    } 
    else {
        std::cerr << "No se pudieron insertar los datos." << std::endl;
    }
}

/**
 * @brief Función principal del programa.
 * 
 * Abre una conexión a la base de datos, crea las tablas necesarias y luego inserta los datos de ejemplo.
 * Finalmente, cierra la conexión a la base de datos.
 * 
 * @return `int` Código de salida del programa.
 */
int main() {
    sqlite3* db; // Declarar base de datos

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Crear tablas
    if (ejecutarSQL(db, SQL_CREATE_TABLES)) {
        std::cout << "Tablas creadas exitosamente." << std::endl;
    }
    else {
        std::cerr << "Error: No se pudieron crear las tablas correctamente." << std::endl;
    }

    // Insertar datos
    insertarDatos(db);

    sqlite3_close(db);
    return 0;
}
