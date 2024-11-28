/**
 * @file Cuenta.hpp
 * @brief Declaración de la clase Cuenta para gestionar cuentas bancarias en la base de datos.
 * @details Este archivo contiene la declaración de la clase Cuenta, la cual proporciona métodos 
 *          para la gestión de operaciones bancarias, incluyendo depósitos, retiros, transferencias,
 *          abonos a préstamos y solicitudes de CDP en una base de datos SQLite.
 * 
 *          La clase también permite verificar la existencia de cuentas, consultar el saldo y 
 *          consultar el historial de transacciones de una cuenta.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 08/11/2024
 */

#ifndef CUENTA_HPP
#define CUENTA_HPP

#include <string>
#include <sqlite3.h>

/**
 * @brief Clase que representa una cuenta bancaria en el sistema.
 * 
 * La clase Cuenta permite realizar y gestionar operaciones bancarias, incluyendo
 * depósitos, retiros, transferencias y abonos a préstamos, así como la creación de 
 * certificados de depósito a plazo (CDP). Se maneja el saldo de cada cuenta y se garantiza 
 * la compatibilidad de moneda en transacciones entre cuentas.
 */
class Cuenta {
    private:
        /// @brief Identificador único de la cuenta en la base de datos.
        int idCuenta = 0;

        /// @brief Identificador único del cliente asociado a la cuenta.
        int idCliente;

        /// @brief Moneda de la cuenta ('USD', 'CRC').
        std::string moneda;

        /// @brief Saldo actual de la cuenta.
        double saldo;

        /// @brief Tasa de interés asociada a la cuenta.
        double tasaInteres;

        /**
         * @brief Actualiza el saldo en la base de datos.
         * 
         * Modifica el saldo de la cuenta en la base de datos para reflejar cambios locales.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @return `true` si la actualización fue exitosa, `false` en caso contrario.
         */
        bool actualizarSaldo(sqlite3* db);

        /**
         * @brief Verifica si existe una cuenta con la misma moneda para el cliente.
         * 
         * Comprueba que el cliente no tenga otra cuenta en la misma moneda antes de crear una nueva.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @return `true` si existe una cuenta con la misma moneda, `false` en caso contrario.
         */
        bool existeSegunMoneda(sqlite3* db);

        /**
         * @brief Verifica si hay fondos suficientes en la cuenta para realizar una operación.
         * 
         * Confirma que el saldo de la cuenta cubra el monto solicitado en operaciones de extracción de fondos.
         * 
         * @param monto Monto a verificar en el saldo.
         * @return `true` si hay fondos suficientes, `false` en caso contrario.
         */
        bool verificarFondos(double monto) const;

        /**
         * @brief Crea una transacción en la base de datos.
         * 
         * Inserta un registro de transacción en la base de datos con los detalles de la operación.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param idRemitente ID de la cuenta remitente.
         * @param idDestinatario ID de la cuenta destinataria.
         * @param tipo Tipo de transacción ("DEP", "RET", "TRA", "ABO", "CDP").
         * @param monto Monto de la transacción.
         * @return `true` si la transacción fue creada con éxito, `false` en caso contrario.
         */
        bool crearTransaccion(sqlite3* db, int idRemitente, int idDestinatario, const std::string& tipo, double monto);

    public:
        /**
         * @brief Constructor de la clase Cuenta.
         * 
         * Inicializa una cuenta con los datos especificados.
         * 
         * @param idCliente Identificador del cliente asociado a la cuenta.
         * @param moneda Moneda de la cuenta ('USD', 'CRC').
         * @param saldo Saldo inicial de la cuenta.
         * @param tasaInteres Tasa de interés asociada a la cuenta.
         */
        Cuenta(int idCliente, const std::string &moneda, double saldo, double tasaInteres);

        /**
         * @brief Crea un nuevo registro de cuenta en la base de datos.
         * 
         * Inserta los datos de la cuenta en la base de datos y asigna un identificador único.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @return `true` si la creación fue exitosa, `false` en caso contrario.
         */
        bool crear(sqlite3* db);

        /**
         * @brief Obtiene una cuenta desde la base de datos a partir de su identificador.
         * 
         * Realiza una consulta para recuperar los datos de una cuenta específica en la base de datos.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param idCuenta Identificador de la cuenta a buscar.
         * @return Objeto Cuenta con los datos obtenidos.
         */
        static Cuenta obtener(sqlite3* db, int idCuenta);

        /**
         * @brief Verifica si una cuenta existe en la base de datos.
         * 
         * Realiza una consulta para confirmar la existencia de una cuenta con el ID dado.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param idCuenta Identificador de la cuenta a verificar.
         * @return `true` si la cuenta existe, `false` en caso contrario.
         */
        static bool existe(sqlite3* db, int idCuenta);

        /**
         * @brief Obtiene el identificador único de la cuenta.
         * 
         * Devuelve el ID asignado a la cuenta en la base de datos.
         * 
         * @return `int` El identificador de la cuenta.
         */
        int getID() const;

        /**
         * @brief Retorna el identificador (ID) del cliente.
         * 
         * @return `int` El identificar de la cliente de la cuenta.
         */
        int getIDCliente() const;

        /**
         * @brief Retorna el tipo de moneda de la cuenta.
         * 
         * @return `std::string` La moneda ('CRC', 'USD').
         */
        std::string getMoneda() const;
        
        /**
         * @brief Consulta el saldo actual de la cuenta.
         * 
         * Muestra el saldo disponible en la cuenta para verificar fondos.
         * 
         * @return `double` El saldo actual de la cuenta.
         */
        double verSaldo() const;

        /**
         * @brief Realiza un depósito en la cuenta.
         * 
         * Aumenta el saldo de la cuenta en el monto especificado.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param monto Monto a depositar.
         * @return `true` si el depósito fue exitoso, `false` en caso contrario.
         */
        bool depositar(sqlite3* db, double monto);

        /**
         * @brief Realiza un retiro en la cuenta.
         * 
         * Disminuye el saldo de la cuenta si hay fondos suficientes.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param monto Monto a retirar.
         * @return `true` si el retiro fue exitoso, `false` en caso contrario.
         */
        bool retirar(sqlite3* db, double monto);

        /**
         * @brief Transfiere fondos de esta cuenta a otra cuenta.
         * 
         * Realiza una transferencia entre cuentas si la moneda es compatible.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param idCuentaDestino Identificador de la cuenta destino.
         * @param monto Monto a transferir.
         * @return `true` si la transferencia fue exitosa, `false` en caso contrario.
         */
        bool transferir(sqlite3* db, int idCuentaDestino, double monto);

        /**
         * @brief Realiza un abono a un préstamo desde la cuenta.
         * 
         * PENDIENTE
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param monto Monto a abonar al préstamo.
         * @return `true` si el abono fue exitoso, `false` en caso contrario.
         */
        bool abonarPrestamo(sqlite3* db, double monto);

        /**
         * @brief Solicita un Certificado de Depósito a Plazo (CDP) desde la cuenta.
         * 
         * Crea un CDP con el monto y plazo especificados, disminuyendo el saldo de la cuenta.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param moneda Tipo de moneda del CDP ('CRC', 'USD')
         * @param monto Monto a depositar en el CDP.
         * @param plazoMeses Plazo del CDP en meses.
         * @return `true` si la solicitud fue exitosa, `false` en caso contrario.
         */
        bool solicitarCDP(sqlite3* db, std::string &moneda, double monto, int plazoMeses, double tasaInteres);

        /**
         * @brief Consulta el historial de transacciones de la cuenta.
         * 
         * Muestra el historial completo de transacciones realizadas en la cuenta.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @return `void`
         */
        void consultarHistorial(sqlite3* db) const; 

        /**
         * @brief Verifica la compatibilidad de moneda entre cuentas para una transferencia.
         * 
         * Asegura que la cuenta de destino tenga la misma moneda antes de realizar la transferencia.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param idCuentaDestino Identificador de la cuenta destino.
         * @return `true` si las cuentas tienen la misma moneda, `false` en caso contrario.
         */
        bool verificarCompatibilidadMoneda(sqlite3* db, int idCuentaDestino) const;
};

#endif // CUENTA_HPP
