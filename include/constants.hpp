/**
 * @file constants.hpp
 * @brief Definición de enumeraciones para las opciones de los menús de la aplicación bancaria.
 * @details Este archivo contiene las enumeraciones que representan las opciones de los
 *          diferentes menús de la aplicación, facilitando la selección y organización
 *          de las opciones en los menús principales y secundarios.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
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
    SOLICITAR_CDP,
    ABONO_PRESTAMO,
    DEPOSITO,
    TRANSFERENCIA,
    RETIRO,
    REGRESAR
};

#endif // CONSTANTS_HPP
