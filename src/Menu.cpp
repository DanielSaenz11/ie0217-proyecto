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
        
        opcionOperacion = obtenerEntero();

        switch (static_cast<OperacionesCliente>(opcionOperacion)) {
            case OperacionesCliente::VER_SALDO: {
                std::cout << "Saldo actual: " << cuenta.verSaldo() << std::endl;
                break;
            }
            case OperacionesCliente::CONSULTAR_HISTORIAL: {
                cuenta.consultarHistorial(db);
                break;
            }
            case OperacionesCliente::SOLICITAR_CDP: {
                
                std::cout << "Opción en construcción." << std::endl;
                break;
                // std::cout << "Ingrese monto para CDP: ";
                // double monto = obtenerDecimal();
                // std::cout << "Ingrese plazo en meses: ";
                // int plazoMeses = obtenerEntero();

                // if (cuenta.solicitarCDP(db, monto, plazoMeses)) {
                //     std::cout << "CDP solicitado con éxito." << std::endl;
                // } else {
                //     std::cout << "Error al solicitar CDP." << std::endl;
                // }
                // break;
            }
            case OperacionesCliente::ABONO_PRESTAMO: {
                std::cout << "Opción en construcción." << std::endl;
                break;
                // std::cout << "Ingrese ID del préstamo a abonar: ";
                // int idPrestamo = obtenerEntero();

                // std::cout << "Ingrese monto a abonar: ";
                // double monto = obtenerDecimal();

                // if (cuenta.abonarPrestamo(db, idPrestamo, monto)) {
                //     std::cout << "Abono realizado con éxito." << std::endl;
                // } else {
                //     std::cout << "Error en el abono al préstamo." << std::endl;
                // }
                // break;
            }
            case OperacionesCliente::DEPOSITO: {
                std::cout << "Ingrese monto a depositar: ";
                double montoDeposito = obtenerDecimal();

                if (cuenta.depositar(db, montoDeposito)) {
                    std::cout << "Depósito realizado con éxito." << std::endl;
                }
                break;
            }
            case OperacionesCliente::TRANSFERENCIA: {
                std::cout << "Ingrese ID de la cuenta destino: ";
                int idCuentaDestino = obtenerEntero();
                
                std::cout << "Ingrese monto a transferir: ";
                double montoTransferencia = obtenerDecimal();

                if (cuenta.transferir(db, idCuentaDestino, montoTransferencia)) {
                    std::cout << "Transferencia realizada con éxito." << std::endl;
                }
                break;
            }
            case OperacionesCliente::RETIRO: {
                std::cout << "Ingrese monto a retirar: ";
                double montoRetiro = obtenerDecimal();

                if (cuenta.retirar(db, montoRetiro)) {
                    std::cout << "Retiro realizado con éxito." << std::endl;
                } else {
                    std::cout << "Error en el retiro." << std::endl;
                }
                break;
            }
            case OperacionesCliente::REGRESAR: {
                std::cout << "Regresando al menú de selección de cuenta." << std::endl;
                break;
            }
            default: {
                std::cout << "Opción inválida en el menú de operaciones." << std::endl;
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

        switch (static_cast<MenuAtencionClienteOpciones>(opcionAtencion)) {
            case MenuAtencionClienteOpciones::INICIAR_SESION: {
                std::cout << "Ingrese la cédula del cliente: ";
                int cedula = obtenerEntero();

                // Verificar si existe un cliente con la cédula ingresada y obtener el ID de ese cliente
                Cliente cliente = Cliente::obtener(db, cedula);
                int idCliente = cliente.getID();

                if (idCliente == 0) {
                    break;
                }

                int opcionCuenta;
                std::cout << "\n1. Crear nueva cuenta\n2. Acceder a cuenta existente\nSeleccione una opción: ";
                opcionCuenta = obtenerEntero();

                if (opcionCuenta == 1) {
                    std::string moneda = validarMoneda();

                    std::cout << "Ingrese saldo inicial: ";
                    double saldoInicial = obtenerDecimal();

                    std::cout << "Ingrese tasa de interés: ";
                    double tasaInteres = obtenerDecimal();

                    Cuenta nuevaCuenta(idCliente, moneda, saldoInicial, tasaInteres);

                    if (nuevaCuenta.crear(db)) {
                        std::cout << "Cuenta creada con éxito.\nID de la cuenta: " << nuevaCuenta.getID() << std::endl;
                    } else {
                        std::cout << "Error al crear la cuenta." << std::endl;
                    }
                }
                else if (opcionCuenta == 2) {
                    std::cout << "Ingrese el ID de la cuenta: ";
                    int idCuenta = obtenerEntero();
                    
                    Cuenta cuenta = Cuenta::obtener(db, idCuenta);

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
                std::cout << "Ingrese cédula: ";
                int cedula = obtenerEntero();

                if (Cliente::existe(db, cedula)) {
                    std::cout << "Error: El cliente ya está registrado." << std::endl;
                    break;
                }

                std::cout << "Ingrese nombre: ";
                std::string nombre;
                std::cin >> nombre;

                std::cout << "Ingrese primer apellido: ";
                std::string primerApellido;
                std::cin >> primerApellido;

                std::cout << "Ingrese segundo apellido: ";
                std::string segundoApellido;
                std::cin >> segundoApellido;

                std::string telefono = validarTelefono();

                Cliente cliente(cedula, nombre, primerApellido, segundoApellido, telefono);
                if (cliente.crear(db)) {
                    std::cout << "Cliente registrado con éxito." << std::endl;
                } else {
                    std::cout << "Error al registrar cliente." << std::endl;
                }
                break;
            }
            case MenuAtencionClienteOpciones::REGRESAR:
                std::cout << "Regresando al menú principal." << std::endl;
                break;
            default:
                std::cout << "Opción inválida en el menú de atención al cliente." << std::endl;
                break;
        }
    } while (opcionAtencion != static_cast<int>(MenuAtencionClienteOpciones::REGRESAR));
}

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    std::cout << "\n=== Menú Principal ===\n";
    std::cout << "1. Atención al Cliente\n";
    std::cout << "2. Préstamo Bancario\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opción: ";
}

