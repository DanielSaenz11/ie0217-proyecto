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
    
    CREATE TABLE IF NOT EXISTS Cuentas (
        idCuenta INTEGER PRIMARY KEY AUTOINCREMENT,
        idCliente INTEGER NOT NULL,
        moneda TEXT NOT NULL CHECK (moneda IN ('CRC', 'USD')),
        saldo REAL NOT NULL,
        tasaInteres REAL NOT NULL,
        FOREIGN KEY (idCliente) REFERENCES Clientes(idCliente)
    );
    
    CREATE TABLE IF NOT EXISTS CDP (
        idCDP INTEGER PRIMARY KEY AUTOINCREMENT,
        idCuenta INTEGER NOT NULL,
        deposito REAL NOT NULL,
        plazoMeses INTEGER NOT NULL,
        tasaInteres REAL NOT NULL,
        fechaSolicitud TEXT NOT NULL,
        FOREIGN KEY (idCuenta) REFERENCES Cuentas(idCuenta)
    );

    CREATE TABLE IF NOT EXISTS Transacciones (
        idTransaccion INTEGER PRIMARY KEY AUTOINCREMENT,
        idRemitente INTEGER,
        idDestinatario INTEGER,
        tipo TEXT NOT NULL CHECK (tipo IN ('DEP', 'RET', 'TRA', 'ABO', 'CDP')),
        monto REAL NOT NULL,
        FOREIGN KEY (idRemitente) REFERENCES Cuentas(idCuenta),
        FOREIGN KEY (idDestinatario) REFERENCES Cuentas(idCuenta)
    );

    CREATE TABLE IF NOT EXISTS Prestamos (
        idPrestamo INTEGER PRIMARY KEY AUTOINCREMENT,
        idCuenta INTEGER NOT NULL,
        tipo TEXT NOT NULL CHECK (tipo IN ('PER', 'PRE', 'HIP')),
        monto REAL NOT NULL,
        tasaInteres REAL NOT NULL,
        plazoMeses INTEGER NOT NULL,
        cuotaMensual REAL NOT NULL,
        capitalPagado REAL NOT NULL,
        interesesPagados REAL NOT NULL,
        saldoRestante REAL NOT NULL,
        fechaSolicitud TEXT NOT NULL,
        fechaSiguientePago TEXT NOT NULL,
        activo BOOLEAN NOT NULL DEFAULT 1,
        FOREIGN KEY (idCuenta) REFERENCES Cuentas(idCuenta)
    );

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
 * @param db Puntero a la base de datos SQLite.
 * @param sql Comando SQL a ejecutar.
 * @details Esta función intenta ejecutar el comando SQL especificado en la base de datos.
 */
void ejecutarSQL(sqlite3* db, const char* sql) {
    char* errMsg = nullptr; // Mensaje de error

    // Ejecución de comando SQL
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Inserta datos de ejemplo en las tablas de la base de datos.
 * 
 * Esta función inserta datos de ejemplo en las tablas Clientes, Cuentas, CDP, Transacciones,
 * Prestamos y PagoPrestamos, con datos ficticios para representar clientes, cuentas y transacciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void insertarDatos(sqlite3* db) {
    const char* sqlInsertarDatos = R"(
        -- Insertar datos en Clientes
        INSERT INTO Clientes (cedula, nombre, primerApellido, segundoApellido, telefono) VALUES 
        (101010101, 'Juan', 'Perez', 'Garcia', '12345678'),
        (202020202, 'Maria', 'Lopez', 'Fernandez', '87654321'),
        (303030303, 'Carlos', 'Ramirez', 'Soto', '45678901'),
        (404040404, 'Ana', 'Jimenez', 'Mora', '23456789');

        -- Insertar datos en Cuentas
        INSERT INTO Cuentas (idCliente, moneda, saldo, tasaInteres) VALUES 
        (1, 'CRC', 150000.0, 2.5),
        (1, 'USD', 500.0, 1.5),
        (2, 'CRC', 200000.0, 2.0),
        (3, 'CRC', 100000.0, 2.0),
        (3, 'USD', 350.0, 1.2),
        (4, 'CRC', 250000.0, 2.7);

        -- Insertar datos en CDP
        INSERT INTO CDP (idCuenta, deposito, plazoMeses, tasaInteres, fechaSolicitud) VALUES
        (1, 60000.0, 12, 2.5, '2024-01-10'),
        (3, 120000.0, 24, 3.0, '2024-02-15'),
        (5, 500.0, 18, 2.8, '2024-03-20');

        -- Insertar transacciones
        INSERT INTO Transacciones (idRemitente, idDestinatario, tipo, monto) VALUES 
        (1, 2, 'TRA', 25000.0),
        (2, NULL, 'RET', 3000.0),
        (NULL, 1, 'DEP', 12000.0),
        (3, 4, 'TRA', 45000.0),
        (NULL, 1, 'CDP', 1000.0),
        (5, NULL, 'ABO', 250.0);

        -- Insertar préstamos
        INSERT INTO Prestamos (idCuenta, tipo, monto, tasaInteres, plazoMeses, cuotaMensual, capitalPagado, interesesPagados, saldoRestante, fechaSolicitud, fechaSiguientePago, activo) VALUES 
        (1, 'PER', 100000.0, 5.0, 24, 5000.0, 10000.0, 2500.0, 87500.0, '2024-11-01', '2024-12-01', 1),
        (5, 'HIP', 50000.0, 3.5, 120, 1500.0, 3000.0, 750.0, 46250.0, '2024-10-15', '2024-11-15', 1);

        -- Insertar datos en PagoPrestamos
        INSERT INTO PagoPrestamos (idPrestamo, cuotaPagada, aporteCapital, aporteIntereses, saldoRestante) VALUES 
        (1, 5000.0, 4000.0, 1000.0, 83500.0),
        (1, 5000.0, 4200.0, 800.0, 79300.0),
        (2, 1500.0, 1200.0, 300.0, 45000.0);
    )";

    ejecutarSQL(db, sqlInsertarDatos); // Ejecución del comando de inserción de datos
    std::cout << "Datos insertados exitosamente en todas las tablas." << std::endl;
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
    ejecutarSQL(db, SQL_CREATE_TABLES);
    std::cout << "Tablas creadas exitosamente." << std::endl;

    // Insertar datos
    insertarDatos(db);

    sqlite3_close(db);
    return 0;
}
