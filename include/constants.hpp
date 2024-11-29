/**
 * @file constants.hpp
 * @brief Definición de enumeraciones para las opciones de los menús de la aplicación bancaria.
 * @details Este archivo contiene las enumeraciones que representan las opciones de los
 *          diferentes menús de la aplicación, facilitando la selección y organización
 *          de las opciones en los menús principales y secundarios.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/**
 * @enum MenuPrincipalOpciones
 * @brief Opciones del menú principal de la aplicación.
 * 
 * Enumeración que representa las opciones disponibles en el menú principal:
 * - ATENCION_CLIENTE: Opción para ir al menú de atención al cliente.
 * - PRESTAMO_BANCARIO: Opción para acceder a información sobre préstamos bancarios.
 * - SALIR: Opción para salir de la aplicación.
 */
enum class MenuPrincipalOpciones {
    ATENCION_CLIENTE = 1,
    PRESTAMO_BANCARIO,
    SALIR
};

/**
 * @enum MenuAtencionClienteOpciones
 * @brief Opciones del menú de atención al cliente.
 * 
 * Enumeración que representa las opciones en el menú de atención al cliente:
 * - INICIAR_SESION: Opción para iniciar sesión con un cliente existente.
 * - REGISTRAR_CLIENTE: Opción para registrar un nuevo cliente.
 * - REGRESAR: Opción para regresar al menú principal.
 */
enum class MenuAtencionClienteOpciones {
    INICIAR_SESION = 1,
    REGISTRAR_CLIENTE,
    REGRESAR
};

/**
 * @enum MenuCuentaOpciones
 * @brief Opciones del menú de gestión de cuentas.
 * 
 * Enumeración que representa las opciones disponibles al gestionar cuentas:
 * - CREAR_CUENTA: Opción para crear una nueva cuenta.
 * - ACCEDER_CUENTA: Opción para acceder a una cuenta existente.
 * - REGRESAR: Opción para regresar al menú anterior.
 */
enum class MenuCuentaOpciones {
    CREAR_CUENTA = 1,
    ACCEDER_CUENTA,
    REGRESAR
};

/**
 * @enum OperacionesCliente
 * @brief Opciones del menú de operaciones de un cliente autenticado.
 * 
 * Enumeración que representa las operaciones disponibles para un cliente:
 * - VER_SALDO: Opción para ver el saldo de la cuenta.
 * - CONSULTAR_HISTORIAL: Opción para consultar el historial de transacciones.
 * - SOLICITAR_CDP: Opción para solicitar un Certificado de Depósito a Plazo (CDP).
 * - ABONO_PRESTAMO: Opción para realizar un abono a un préstamo.
 * - DEPOSITO: Opción para realizar un depósito en la cuenta.
 * - TRANSFERENCIA: Opción para realizar una transferencia a otra cuenta.
 * - RETIRO: Opción para retirar fondos de la cuenta.
 * - REGRESAR: Opción para regresar al menú de selección de cuenta.
 */
enum class OperacionesCliente {
    VER_SALDO = 1,
    CONSULTAR_HISTORIAL,
    VER_CDP,
    ABONO_PRESTAMO,
    DEPOSITO,
    TRANSFERENCIA,
    RETIRO,
    REGRESAR
};

/**
 * @enum MenuPrestamosOpciones
 * @brief Opciones del menú de préstamos.
 * 
 * Enumeración que representa las acciones disponibles en el menú de préstamos:
 * - SOLICITAR_PRESTAMO: Opción para solicitar un nuevo préstamo.
 * - CONSULTAR_PRESTAMOS: Opción para consultar los préstamos existentes.
 * - REGRESAR: Opción para regresar al menú principal.
 */
enum class MenuPrestamosOpciones {
    SOLICITAR_PRESTAMO = 1,
    CONSULTAR_PRESTAMOS,
    REGRESAR
};

/**
 * @enum OpcionesCDP
 * @brief Opciones del submenú de certificados de depósito a plazo (CDP).
 * 
 * Enumeración que representa las acciones relacionadas con los CDP:
 * - SOLICITAR: Opción para solicitar un nuevo CDP.
 * - VER_ESTADO: Opción para consultar el estado de un CDP existente.
 * - REGRESAR: Opción para regresar al menú de operaciones.
 */
enum class OpcionesCDP {
    SOLICITAR = 1,
    VER_ESTADO,
    REGRESAR
};

/**
 * @enum OpcionesAbono
 * @brief Opciones del submenú de abonos a préstamos.
 * 
 * Enumeración que representa las acciones para realizar abonos a préstamos:
 * - PRESTAMO_PROPIO: Opción para abonar a un préstamo propio.
 * - PRESTAMO_TERCEROS: Opción para abonar a un préstamo de terceros.
 * - REGRESAR: Opción para regresar al menú anterior.
 */
enum class OpcionesAbono {
    PRESTAMO_PROPIO = 1,
    PRESTAMO_TERCEROS,
    REGRESAR
};

/**
 * @enum TipoPrestamo
 * @brief Tipos de préstamos disponibles.
 * 
 * Enumeración que define los tipos de préstamos que la aplicación soporta:
 * - PERSONAL: Préstamo personal.
 * - PRENDARIO: Préstamo prendario.
 * - HIPOTECARIO: Préstamo hipotecario.
 */
enum class TipoPrestamo {
    PERSONAL = 1,
    PRENDARIO,
    HIPOTECARIO
};

/**
 * @struct ValoresPrestamo
 * @brief Estructura para definir los valores predeterminados de los préstamos.
 * 
 * Esta estructura incluye los datos clave de un préstamo:
 * - monto: Monto total del préstamo.
 * - cuotaMensual: Valor estimado de la cuota mensual.
 * - plazoMeses: Duración del préstamo en meses.
 * - tasaInteres: Tasa de interés anual aplicada al préstamo.
 */
struct ValoresPrestamo {
    double monto;
    double cuotaMensual;
    int plazoMeses;
    double tasaInteres;
};

/**
 * @namespace Prestamos
 * @brief Espacio de nombres para valores predeterminados de préstamos.
 * 
 * Este namespace organiza los valores predeterminados de los préstamos
 * para las monedas de colones y dólares.
 */
namespace Prestamos {
    /**
     * @namespace Colones
     * @brief Valores predeterminados para préstamos en colones.
     */
    namespace Colones {
        const ValoresPrestamo PERSONAL = {260000, 23222.44, 12, 13.5};
        const ValoresPrestamo PRENDARIO = {15000000, 250367, 72, 6.25};
        const ValoresPrestamo HIPOTECARIO = {45000000, 251286, 360, 5.35};
    }

    /**
     * @namespace Dolares
     * @brief Valores predeterminados para préstamos en dólares.
     */
    namespace Dolares {
        const ValoresPrestamo PERSONAL = {6000, 306.842, 24, 20.5};
        const ValoresPrestamo PRENDARIO = {23500, 396.226, 84, 10.5};
        const ValoresPrestamo HIPOTECARIO = {120000, 791.603, 300, 6.25};
    }
}

/**
 * @struct ValoresCDP
 * @brief Estructura para definir los valores predeterminados de los CDP.
 * 
 * Esta estructura incluye los datos clave de un CDP:
 * - monto: Monto total del certificado.
 * - plazoMeses: Duración del CDP en meses.
 * - tasaInteres: Tasa de interés anual aplicada.
 * - interesesAGanar: Intereses estimados a ganar.
 */
struct ValoresCDP {
    double monto;
    int plazoMeses;
    double tasaInteres;
    double interesesAGanar;
};

/**
 * @namespace CDP_DEF
 * @brief Espacio de nombres para valores predeterminados de CDP.
 * 
 * Contiene valores predeterminados para certificados de depósito a plazo
 * en colones y dólares.
 */
namespace CDP_DEF {
    const ValoresCDP Colones = {500000.0, 6, 4.68, 11700.0};
    const ValoresCDP Dolares = {6000.0, 12, 3.83, 230.0};
}

#endif // CONSTANTS_HPP
