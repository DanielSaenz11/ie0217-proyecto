/**
 * @file Prestamo.cpp
 * @brief Implementación de la clase PPrestamo para gestionar los prestamos en la base de datos.
 * @details Este archivo contiene la definición del método de la clase Prestamo, que permiten
 *          crear un préstmo, abonar al mismo, obtener dato y generar reportes de los mismos. 
 *          Se incluyen funcionalidades para realizar las validaciones de los datos necesarios y 
 *          el manejo de errores correspondiente. 
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#include "Prestamo.hpp"
#include "auxiliares.hpp"
#include "SQLiteStatement.hpp"
#include "Transaccion.hpp"
#include "PagoPrestamo.hpp"
#include "constants.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>


// Definición del constructor de la clase Prestamo
Prestamo::Prestamo(
    int idCuenta,
    const std::string& tipo,
    const std::string &moneda,
    double monto,
    double tasaInteres,
    int plazoMeses,
    double cuotaMensual,
    int cuotasPagadas,
    double capitalPagado,
    double interesesPagados,
    bool activo
) : idCuenta(idCuenta),
    tipo(tipo),
    moneda(moneda),
    monto(monto),
    tasaInteres(tasaInteres),
    plazoMeses(plazoMeses),
    cuotasPagadas(cuotasPagadas),
    capitalPagado(capitalPagado),
    interesesPagados(interesesPagados),
    activo(activo) {

    // Verificar si se ingresó un parámetro con la cuota mensual en el constructor (préstamo existente) o nuevo
    if (cuotaMensual == -1) {
        this->cuotaMensual = calcularCuotaMensual(this->monto, this->tasaInteres, this->plazoMeses);
    }
    else {
        this->cuotaMensual = cuotaMensual;
    }
}


// Definición de función para calcular el monto de intereses
double Prestamo::calcularIntereses() {
    return (monto * tasaInteres / 100) / 12;
}

// Definición de la función para crear un préstamo
bool Prestamo::crear(sqlite3* db) {
    try {
        // Consulta SQL para insertar un nuevo préstamo
        const std::string sql = "INSERT INTO Prestamos (idCuenta, tipo, moneda, monto, tasaInteres, plazoMeses, "
                                "cuotaMensual, cuotasPagadas, capitalPagado, interesesPagados, activo) "
                                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

        SQLiteStatement statement(db, sql);

        // Bind de los valores al statement
        sqlite3_bind_int(statement.get(), 1, idCuenta);
        sqlite3_bind_text(statement.get(), 2, tipo.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement.get(), 3, moneda.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(statement.get(), 4, monto);
        sqlite3_bind_double(statement.get(), 5, tasaInteres);
        sqlite3_bind_int(statement.get(), 6, plazoMeses);
        sqlite3_bind_double(statement.get(), 7, cuotaMensual);
        sqlite3_bind_int(statement.get(), 8, cuotasPagadas);
        sqlite3_bind_double(statement.get(), 9, capitalPagado);
        sqlite3_bind_double(statement.get(), 10, interesesPagados);
        sqlite3_bind_int(statement.get(), 11, activo ? 1 : 0);

        // Ejecutar la consulta
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error al insertar el préstamo en la base de datos.");
        }

        idPrestamo = sqlite3_last_insert_rowid(db);
        std::cout << "Préstamo creado con éxito. ID: " << idPrestamo << std::endl;
        
        // Agregar depósito del préstamo solicitado

        
        return true;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}


bool Prestamo::existe(sqlite3* db, int idPrestamo) {
    const char* sql = "SELECT COUNT(1) FROM Prestamos WHERE idPrestamo = ?;";

    try {
        SQLiteStatement statement(db, sql);
        sqlite3_bind_int(statement.get(), 1, idPrestamo);

        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            return sqlite3_column_int(statement.get(), 0) > 0;
        } else {
            throw std::runtime_error("Error: No se pudo ejecutar la consulta para verificar la existencia del préstamo.");
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}


// Definición de función estática para obtener un préstamo de la base de datos
Prestamo Prestamo::obtener(sqlite3* db, int idPrestamo) {
    // Consulta SQL para seleccionar datos del préstamo a partir de su ID
    std::string sql = "SELECT idCuenta, tipo, moneda, monto, tasaInteres, plazoMeses, cuotaMensual, "
                      "cuotasPagadas, capitalPagado, interesesPagados, activo "
                      "FROM Prestamos WHERE idPrestamo = ?;";

    // Crear un préstamo vacío
    Prestamo prestamo(0, "", "", 0, 0, 0);

    try {
        SQLiteStatement statement(db, sql);

        // Asignar el valor del ID al parámetro de la consulta
        sqlite3_bind_int(statement.get(), 1, idPrestamo);

        // Ejecutar la consulta y verificar si se encontró un registro
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Asignar los valores obtenidos de la base de datos al objeto préstamo
            prestamo.idPrestamo = idPrestamo;
            prestamo.idCuenta = sqlite3_column_int(statement.get(), 0);
            prestamo.tipo = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 1));
            prestamo.moneda = reinterpret_cast<const char*>(sqlite3_column_text(statement.get(), 2));
            prestamo.monto = sqlite3_column_double(statement.get(), 3);
            prestamo.tasaInteres = sqlite3_column_double(statement.get(), 4);
            prestamo.plazoMeses = sqlite3_column_int(statement.get(), 5);
            prestamo.cuotaMensual = sqlite3_column_double(statement.get(), 6);
            prestamo.cuotasPagadas = sqlite3_column_int(statement.get(), 7);
            prestamo.capitalPagado = sqlite3_column_double(statement.get(), 8);
            prestamo.interesesPagados = sqlite3_column_double(statement.get(), 9);
            prestamo.activo = sqlite3_column_int(statement.get(), 10) == 1;
        } else {
            throw std::runtime_error("Error: Préstamo no encontrado con el ID ingresado.");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return prestamo;
}

// Definición de la función para calcular la cuota mensual del préstamo
double Prestamo::calcularCuotaMensual(double monto, double tasaInteres, int plazoMeses) {
    double tasaInteresMensual = (tasaInteres/100) / 12;

    double a = 1 + tasaInteresMensual;

    double cuotaMensual = (monto * tasaInteresMensual * potencia(a, plazoMeses)) / (potencia(a, plazoMeses) - 1);

    return cuotaMensual;
}


bool Prestamo::abonarCuota(sqlite3* db, Cuenta& cuenta) {
    try {

        if (cuenta.getMoneda() != this->moneda) {
            std::cerr << "Error: Los tipos de moneda entre la cuenta y el préstamo no coinciden." << std::endl;
            return false;
        }

        // Iniciar la transacción en la base de datos
        if (sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Error: No se pudo iniciar la transacción.");
        }

        // Reducir los fondos de la cuenta y registrar la transacción
        if (!cuenta.abonarPrestamo(db, cuotaMensual)) {
            throw std::runtime_error("Error: No se pudo realizar el abono desde la cuenta.");
        }

        // Actualizar los datos del préstamo
        double interesesFijos = calcularIntereses();

        // Calcular capital a abonar
        double abonoCapital = cuotaMensual - interesesFijos;

        cuotasPagadas++;
        capitalPagado += abonoCapital;
        interesesPagados += interesesFijos;

        // Si se han pagado todas las cuotas, marcar el préstamo como inactivo
        if (cuotasPagadas >= plazoMeses) {
            std::cout << "El préstamo fue pagado en su totalidad." << std::endl;
            activo = false;
        }

        if (!actualizarDatosAbono(db)) {
            cuotasPagadas--;
            capitalPagado -= abonoCapital;
            interesesPagados -= interesesFijos;
            throw std::runtime_error("Error: No se pudieron actualizar los datos del préstamo.");
        }

        // Crear objeto de la clase PagoPrestamo para registrar la transacción
        PagoPrestamo pago(idPrestamo, cuotaMensual, abonoCapital, interesesFijos, monto - capitalPagado);

        if (!pago.crear(db)) {
            cuotasPagadas--;
            capitalPagado -= abonoCapital;
            interesesPagados -= interesesFijos;
            throw std::runtime_error("Error: No se pudo guardar el movimiento del pago del préstamo.");
        }

        // Confirmar la transacción en la base de datos
        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            cuotasPagadas--;
            capitalPagado -= abonoCapital;
            interesesPagados -= interesesFijos;
            throw std::runtime_error("Error: No se pudo confirmar la transacción.");
        }

        return true;

    } catch (const std::exception& e) {
        // Realizar rollback en caso de error
        std::cerr << e.what() << std::endl;
        if (sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, nullptr) != SQLITE_OK) {
            std::cerr << "Error: No se pudo realizar el rollback." << std::endl;
        }
        return false;
    }
}


bool Prestamo::actualizarDatosAbono(sqlite3* db) {
    try {
        // Consulta SQL para actualizar los datos del préstamo
        const std::string sql = "UPDATE Prestamos SET cuotasPagadas = ?, capitalPagado = ?, interesesPagados = ?, activo = ? WHERE idPrestamo = ?;";
        SQLiteStatement statement(db, sql);

        // Asignar los valores actualizados a la consulta
        sqlite3_bind_int(statement.get(), 1, cuotasPagadas);
        sqlite3_bind_double(statement.get(), 2, capitalPagado);
        sqlite3_bind_double(statement.get(), 3, interesesPagados);
        sqlite3_bind_int(statement.get(), 4, activo ? 1 : 0);
        sqlite3_bind_int(statement.get(), 5, idPrestamo);

        // Ejecutar la consulta
        if (sqlite3_step(statement.get()) != SQLITE_DONE) {
            throw std::runtime_error("Error: No se pudo actualizar los datos del préstamo en la base de datos.");
        }

        return true; // Actualización exitosa

    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void Prestamo::mostrarHistorialAbonos(sqlite3* db) const {
    // Consulta SQL para obtener los pagos asociados al préstamo
    std::string sql = "SELECT cuotaPagada, aporteCapital, aporteIntereses FROM PagoPrestamos WHERE idPrestamo = ?;";
    
    try {
        // Crear statement para manejar la consulta
        SQLiteStatement statement(db, sql);

        // Asignar el idPrestamo como parámetro de la consulta
        sqlite3_bind_int(statement.get(), 1, idPrestamo);

        // Encabezado para la tabla de historial de pagos
        std::cout << "=== Historial de Pagos para el Préstamo ID " << idPrestamo << " ===" << std::endl;
        std::cout << "Cuota Pagada\tAporte Capital\tAporte Intereses" << std::endl;

        // Recorrer los resultados de la consulta
        while (sqlite3_step(statement.get()) == SQLITE_ROW) {
            double cuotaPagada = sqlite3_column_double(statement.get(), 0);
            double aporteCapital = sqlite3_column_double(statement.get(), 1);
            double aporteIntereses = sqlite3_column_double(statement.get(), 2);

            // Mostrar los resultados en formato de tabla
            std::cout << cuotaPagada << "\t\t" << aporteCapital << "\t\t" << aporteIntereses << std::endl;
        }
    } catch (const std::exception& e) {
        // Manejo de errores
        std::cerr << "Error al mostrar el historial de pagos: " << e.what() << std::endl;
    }
}


// Definición de función que retorna el ID del préstamo
int Prestamo::getID() const {
    return idPrestamo;
}

int Prestamo::getIDCuenta() const {
    return idCuenta;
}

// Definición de función para establecer el ID de la cuenta asociada
bool Prestamo::setIDCuenta(int idCuenta) {
    if (idCuenta > 0) {
        this->idCuenta = idCuenta;
        return true;
    }
    return false;
}

// Definición de método para mostrar la información del préstamo requerida para hacer un abono
void Prestamo::mostrarInformacionPago() const {
    std::cout << "==== Información del Préstamo ====" << std::endl;
    std::cout << "ID del Préstamo: " << idPrestamo << std::endl;
    std::cout << "Cuota mensual: " << cuotaMensual << std::endl;
}

// Definición de método estático para realizar la consulta del estado de un préstamo
bool Prestamo::consultarEstado(sqlite3* db, int idPrestamo, const std::string& nombreArchivo) {
    // Consulta SQL para recuperar datos del préstamo
    std::string sql = R"(
        SELECT cuotaMensual, cuotasPagadas, capitalPagado, interesesPagados, plazoMeses 
        FROM Prestamos WHERE idPrestamo = ?;
    )";

    try {
        // Preparar statement con SQLiteStatement
        SQLiteStatement statement(db, sql);

        // Enlazar el ID del préstamo como parámetro
        sqlite3_bind_int(statement.get(), 1, idPrestamo);

        // Ejecutar la consulta
        if (sqlite3_step(statement.get()) == SQLITE_ROW) {
            // Recuperar datos del préstamo
            double cuotaMensual = sqlite3_column_double(statement.get(), 0);
            int cuotasPagadas = sqlite3_column_int(statement.get(), 1);
            double capitalPagado = sqlite3_column_double(statement.get(), 2);
            double interesesPagados = sqlite3_column_double(statement.get(), 3);
            int plazoMeses = sqlite3_column_int(statement.get(), 4);

            // Calcular cuotas restantes
            int cuotasRestantes = plazoMeses - cuotasPagadas;

            // Mostrar datos al usuario
            std::cout << "==== Estado del Préstamo ====" << std::endl;
            std::cout << "Cuota Mensual: " << cuotaMensual << std::endl;
            std::cout << "Cuotas Pagadas: " << cuotasPagadas << std::endl;
            std::cout << "Aporte al Capital: " << capitalPagado << std::endl;
            std::cout << "Intereses Pagados: " << interesesPagados << std::endl;
            std::cout << "Cuotas Restantes: " << cuotasRestantes << std::endl;

            // Generar reporte si el nombre del archivo no está vacío
            if (!nombreArchivo.empty()) {
                std::ofstream archivo(nombreArchivo);
                if (!archivo.is_open()) {
                    throw std::ios_base::failure("Error: No se pudo abrir el archivo para guardar el estado del préstamo.");
                }

                // Escribir los datos en formato CSV
                archivo << "Cuota Mensual,Cuotas Pagadas,Aporte al Capital,Intereses Pagados,Cuotas Restantes\n";
                archivo << cuotaMensual << "," << cuotasPagadas << "," << capitalPagado << "," << interesesPagados << "," << cuotasRestantes << "\n";
                archivo.close();

                std::cout << "Estado del préstamo guardado en el archivo: " << nombreArchivo << std::endl;
            } else {
                std::cout << "Reporte no generado." << std::endl;
            }

            return true;
        } else {
            throw std::runtime_error("Error: No se encontró el préstamo con el ID especificado.");
        }
    } catch (const std::exception& e) {
        // Manejar errores
        std::cerr << e.what() << std::endl;
        return false;
    }
}


void Prestamo::reportePagoEstimado(const std::string& moneda, double monto, int plazoMeses, double tasaInteres, double cuotaMensual) {
    // Mostrar los detalles del préstamo en forma de tabla
    std::cout << "\n=== Resumen del Préstamo Estimado ===" << std::endl;
    std::cout << std::setw(12) << "Moneda" 
              << std::setw(15) << "Monto Total" 
              << std::setw(15) << "Plazo (Meses)" 
              << std::setw(10) << "Tasa (%)" 
              << std::setw(15) << "Cuota Mensual" << std::endl;
    std::cout << std::setw(12) << moneda 
              << std::setw(15) << monto 
              << std::setw(15) << plazoMeses 
              << std::setw(10) << tasaInteres 
              << std::setw(15) << cuotaMensual << std::endl;

    // Preguntar al usuario si desea guardar el reporte
    std::cout << "\n¿Desea guardar este reporte en un archivo? (s/n): ";
    bool guardarArchivo = validarRespuestaSN();

    if (guardarArchivo) {
        // Solicitar el nombre del archivo
        std::cout << "Ingrese el nombre del archivo (con extensión .csv): ";
        std::string nombreArchivo = obtenerArchivoCSV();

        // Guardar los datos en el archivo
        std::ofstream archivo(nombreArchivo);

        // Abrir archivo
        if (!archivo.is_open()) {
            std::cerr << "Error al guardar el archivo.\n";
        }

        // Escribir títulos en el archivo valores de las variables a almacenar
        archivo << std::fixed << std::setprecision(2); // Salida con dos decimales
        archivo << "Moneda,Monto Total,Plazo en Meses,Tasa de Interés,Cuota Mensual\n";
        archivo << moneda << "," << monto << "," << plazoMeses << "," 
                << tasaInteres << "," << cuotaMensual << "\n";
        
        archivo.close();// Cerrar el archivo

        // Mensaje de verificación
        std::cout << "Reporte guardado en " << nombreArchivo << "\n";
    }
}


ValoresPrestamo Prestamo::obtenerValoresPredeterminados(TipoPrestamo tipo, const std::string &moneda) {
    switch (tipo) {
        case TipoPrestamo::PERSONAL:
            return (moneda == "CRC") ? Prestamos::Colones::PERSONAL : Prestamos::Dolares::PERSONAL;
        case TipoPrestamo::PRENDARIO:
            return (moneda == "CRC") ? Prestamos::Colones::PRENDARIO : Prestamos::Dolares::PRENDARIO;
        case TipoPrestamo::HIPOTECARIO:
            return (moneda == "CRC") ? Prestamos::Colones::HIPOTECARIO : Prestamos::Dolares::HIPOTECARIO;
    }
}
