/**
 * @file Menu.cpp
 * @brief Implementación de las funciones de los menús de la aplicación bancaria.
 * @details Este archivo contiene la implementación de las funciones que presentan los menús 
 *          al usuario y manejan las interacciones y opciones del menú principal, menú de atención al cliente,
 *          y menú de operaciones de un cliente autenticado.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#include "Menu.hpp"
#include <iostream>
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "auxiliares.hpp"
#include "constants.hpp"

// Función para el menú de operaciones de la cuenta del cliente
void menuOperacionesCliente(sqlite3* db, Cuenta& cuenta) {
    int opcionOperacion;
    do {
        // Mostrar el menú de operaciones de cliente
        std::cout << "\n=== Menú de Operaciones ===\n";
        std::cout << "1. Ver Saldo\n";
        std::cout << "2. Consultar Historial\n";
        std::cout << "3. Solicitar CDP\n";
        std::cout << "4. Abono a Préstamo\n";
        std::cout << "5. Depósito\n";
        std::cout << "6. Transferencia\n";
        std::cout << "7. Retiro\n";
        std::cout << "8. Regresar\n";
        std::cout << "Seleccione una opción: ";
        
        opcionOperacion = obtenerEntero(); // Validar opción ingresada en el menú

        switch (static_cast<OperacionesCliente>(opcionOperacion)) {
            case OperacionesCliente::VER_SALDO: {
                // Opción para ver el saldo actual de la cuenta
                std::cout << "Saldo actual: " << cuenta.verSaldo() << std::endl;
                break;
            }
            case OperacionesCliente::CONSULTAR_HISTORIAL: {
                // Opción para mostrar el historial de transacciones de la cuenta
                cuenta.consultarHistorial(db);
                break;
            }
            case OperacionesCliente::SOLICITAR_CDP: {
                // Opción para solicitar CDP
                std::cout << "Opción en construcción." << std::endl;
                break;
            }
            case OperacionesCliente::ABONO_PRESTAMO: {
                // Opción para realizar un abono a un préstamo
                std::cout << "Opción en construcción." << std::endl;
                break;
            }
            case OperacionesCliente::DEPOSITO: {
                // Opción para realizar un depósito a la cuenta
                std::cout << "Ingrese monto a depositar: ";
                double montoDeposito = obtenerDecimal(); // Validar monto a depositar

                // Realizar transacción de depósito
                if (cuenta.depositar(db, montoDeposito)) {
                    std::cout << "Depósito realizado con éxito." << std::endl;
                }
                break;
            }
            case OperacionesCliente::TRANSFERENCIA: {
                // Opción para realizar una transferencia entre cuentas del mismo tipo de moneda
                std::cout << "Ingrese ID de la cuenta destino: ";
                int idCuentaDestino = obtenerEntero(); // Validar número de cuenta de destinatario
                
                std::cout << "Ingrese monto a transferir: ";
                double montoTransferencia = obtenerDecimal(); // Validar monto a transferir

                // Realizar la transacción actual
                if (cuenta.transferir(db, idCuentaDestino, montoTransferencia)) {
                    std::cout << "Transferencia realizada con éxito." << std::endl;
                }
                break;
            }
            case OperacionesCliente::RETIRO: {
                // Opción para realizar un retiro
                std::cout << "Ingrese monto a retirar: ";
                double montoRetiro = obtenerDecimal(); // Validar monto a retirar
                
                // Realizar la transacción
                if (cuenta.retirar(db, montoRetiro)) {
                    std::cout << "Retiro realizado con éxito." << std::endl;
                }
                break;
            }
            case OperacionesCliente::REGRESAR: {
                std::cout << "Regresando al menú de selección de cuenta." << std::endl;
                break;
            }
            default: {
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
            }
        }
    } while (opcionOperacion != static_cast<int>(OperacionesCliente::REGRESAR));
}

// Función para el menú de atención al cliente
void menuAtencionCliente(sqlite3* db) {
    int opcionAtencion;

    do {
        // Mostrar el menú de atención al cliente
        std::cout << "\n=== Menú de Atención al Cliente ===\n";
        std::cout << "1. Iniciar Sesión\n";
        std::cout << "2. Registrar Cliente\n";
        std::cout << "3. Regresar\n";
        std::cout << "Seleccione una opción: ";
        
        opcionAtencion = obtenerEntero();

        // Validar opción seleccionada
        switch (static_cast<MenuAtencionClienteOpciones>(opcionAtencion)) {
            case MenuAtencionClienteOpciones::INICIAR_SESION: {
                // Opción para iniciar sesión de cliente

                // Solicitud de cédula de identificación
                std::cout << "Ingrese la cédula del cliente: ";
                int cedula = obtenerEntero();

                // Verificar si existe un cliente con la cédula ingresada y obtener el ID de ese cliente
                Cliente cliente = Cliente::obtener(db, cedula);
                int idCliente = cliente.getID();

                // Si no existe, se sale y vuelve a mostrar el menú
                if (idCliente == 0) {
                    break;
                }

                int opcionCuenta; // Opción respecto a la cuenta con la que desea iniciar sesión
                std::cout << "\n1. Crear nueva cuenta\n2. Acceder a cuenta existente\nSeleccione una opción: ";
                opcionCuenta = obtenerEntero();

                // Clasificar opción de cuenta
                if (opcionCuenta == 1) {
                    // Opción de crear cuenta

                    // Ingreso del tipo de moneda de la cuenta
                    std::string moneda = validarMoneda();

                    // Ingreso del saldo inicial de la cuenta
                    std::cout << "Ingrese saldo inicial: ";
                    double saldoInicial = obtenerDecimal();

                    // Ingreso de la tasa de interés de la cuenta
                    std::cout << "Ingrese tasa de interés: ";
                    double tasaInteres = obtenerDecimal();

                    // Crear instancia de Cuenta con los datos ingresados
                    Cuenta nuevaCuenta(idCliente, moneda, saldoInicial, tasaInteres);

                    // Insertar en la base de datos
                    if (nuevaCuenta.crear(db)) {
                        std::cout << "Cuenta creada con éxito.\nID de la cuenta: " << nuevaCuenta.getID() << std::endl;
                    }
                }
                else if (opcionCuenta == 2) {
                    // Opción de acceder a una cuenta existente

                    // Solicitud del identificador de la cuenta
                    std::cout << "Ingrese el ID de la cuenta: ";
                    int idCuenta = obtenerEntero();
                    
                    // Buscar cuenta con el ID ingresado
                    Cuenta cuenta = Cuenta::obtener(db, idCuenta);

                    // Comprobar que exista la cuenta y que la cuenta pertenezca al cliente actual
                    if (cuenta.getID() == 0 || cuenta.getIDCliente() != idCliente) {
                        std::cout << "Error: La cuenta no existe o no pertenece al cliente." << std::endl;
                        break;
                    }

                    // Mostrar el menú de operaciones de la cuenta
                    menuOperacionesCliente(db, cuenta);
                }
                else {
                    std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                }
                break;
            }
            case MenuAtencionClienteOpciones::REGISTRAR_CLIENTE: {
                // Opción de registrar cliente en el sistema

                // Ingreso de cédula
                std::cout << "Ingrese cédula: ";
                int cedula = obtenerEntero();

                // Verificar que no exista un cliente registrado con el mismo número de cédula
                if (Cliente::existe(db, cedula)) {
                    std::cout << "Error: El cliente ya está registrado." << std::endl;
                    break;
                }

                // Ingreso de nombre
                std::cout << "Ingrese nombre: ";
                std::string nombre;
                std::cin >> nombre;

                // Ingreso de primer apellido
                std::cout << "Ingrese primer apellido: ";
                std::string primerApellido;
                std::cin >> primerApellido;

                // Ingreso de segundo apellido
                std::cout << "Ingrese segundo apellido: ";
                std::string segundoApellido;
                std::cin >> segundoApellido;

                // Ingreso de teléfono
                std::string telefono = validarTelefono();

                // Crear instancia de cliente con los datos ingresados
                Cliente cliente(cedula, nombre, primerApellido, segundoApellido, telefono);
                
                // Insertar cliente en la base de datos
                if (cliente.crear(db)) {
                    std::cout << "Cliente registrado con éxito." << std::endl;
                }
                break;
            }
            case MenuAtencionClienteOpciones::REGRESAR:
                // Opción para salir del menú de atención al cliente
                std::cout << "Regresando al menú principal." << std::endl;
                break;
            default:
                // Caso default para opciones inválidas
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcionAtencion != static_cast<int>(MenuAtencionClienteOpciones::REGRESAR));
}

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    // Formato del menú principal
    std::cout << "\n=== Menú Principal ===\n";
    std::cout << "1. Atención al Cliente\n";
    std::cout << "2. Préstamo Bancario\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opción: ";
}

