/**
 * @file Menu.cpp
 * @brief Implementación de las funciones de los menús de la aplicación bancaria.
 * @details Este archivo contiene la implementación de las funciones que presentan los menús 
 *          al usuario y manejan las interacciones y opciones del menú principal, menú de atención al
 *          cliente, y menú de operaciones de un cliente autenticado, junto con el menú de préstamos.
 *          También contiene la implementación de las subfunciones de los menús anteriores.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @copyright MIT License
 * @date 08/11/2024
 */

#include "Menu.hpp"
#include "Prestamo.hpp"
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "auxiliares.hpp"
#include "constants.hpp"
#include "CDP.hpp"
#include <iostream>

// -------------------------------- Menú principal --------------------------------

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    // Formato del menú principal
    std::cout << "\n=== Menú Principal ===" << std::endl;
    std::cout << "1. Atención al Cliente" << std::endl;
    std::cout << "2. Préstamo Bancario" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

// -------------------------------- Menú de operaciones en la cuenta --------------------------------

// Función para el menú de operaciones de la cuenta del cliente
void menuOperacionesCliente(sqlite3* db, Cuenta& cuenta) {
    int opcionOperacion;
    do {
        // Mostrar el menú de operaciones de cliente
        mostrarMenuOperaciones();
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
            case OperacionesCliente::VER_CDP: {
                manejarCDP(db, cuenta);
                break;
            }
            case OperacionesCliente::ABONO_PRESTAMO: {
                manejarAbonoPrestamo(db, cuenta);
                break;
            }
            case OperacionesCliente::DEPOSITO: {
                realizarDeposito(db, cuenta);
                break;
            }
            case OperacionesCliente::TRANSFERENCIA: {
                realizarTransferencia(db, cuenta);
                break;
            }
            case OperacionesCliente::RETIRO: {
                realizarRetiro(db, cuenta);
                break;
            }
            case OperacionesCliente::REGRESAR: {
                std::cout << "Regresando al menú de atención al cliente." << std::endl;
                break;
            }
            default: {
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
            }
        }
    } while (opcionOperacion != static_cast<int>(OperacionesCliente::REGRESAR));
}

// Mostrar menú de operaciones
void mostrarMenuOperaciones() {
    std::cout << "\n=== Menú de Operaciones ===" << std::endl;
    std::cout << "1. Ver Saldo" << std::endl;
    std::cout << "2. Consultar Historial" << std::endl;
    std::cout << "3. Certificados de Depósito a Plazo" << std::endl;
    std::cout << "4. Abono a Préstamo" << std::endl;
    std::cout << "5. Depósito" << std::endl;
    std::cout << "6. Transferencia" << std::endl;
    std::cout << "7. Retiro" << std::endl;
    std::cout << "8. Regresar" << std::endl;
    std::cout << "Seleccione una opción: ";
}


// Manejar opciones del menú CDP
void manejarCDP(sqlite3* db, Cuenta& cuenta) {
    std::cout << "\n=== Opciones de CDP ===" << std::endl;
    std::cout << "1. Solicitar un nuevo CDP" << std::endl;
    std::cout << "2. Ver estado de un CDP" << std::endl;
    std::cout << "3. Regresar al menú de operaciones" << std::endl;
    std::cout << "Seleccione una opción: ";
    
    int opcionCDP = obtenerEntero();
    switch (static_cast<OpcionesCDP>(opcionCDP)) {
        case OpcionesCDP::SOLICITAR: {
            // Solicitar un nuevo CDP
            std::string moneda = cuenta.getMoneda();
            const ValoresCDP& valoresPredeterminados = (moneda == "CRC") ? CDP_DEF::Colones : CDP_DEF::Dolares;

            std::cout << "\nValores predeterminados para " << (moneda == "CRC" ? "Colones" : "Dólares") << ":\n";
            std::cout << "Monto Total: " << valoresPredeterminados.monto << std::endl;
            std::cout << "Plazo en Meses: " << valoresPredeterminados.plazoMeses << std::endl;
            std::cout << "Tasa de Interés Anual: " << valoresPredeterminados.tasaInteres << "%" << std::endl;
            std::cout << "Intereses a Ganar: " << valoresPredeterminados.interesesAGanar << std::endl;

            // Preguntar si desea usar valores predeterminados
            std::cout << "¿Desea usar estos valores predeterminados? (s/n): ";
            bool usarPredeterminados = validarRespuestaSN();

            double monto;
            int plazoMeses;
            double tasaInteres;

            if (usarPredeterminados) {
                monto = valoresPredeterminados.monto;
                plazoMeses = valoresPredeterminados.plazoMeses;
                tasaInteres = valoresPredeterminados.tasaInteres;
            } else {
                // Solicitar valores personalizados
                std::cout << "Ingrese el monto del depósito: ";
                monto = obtenerDecimal();

                std::cout << "Ingrese el plazo en meses: ";
                plazoMeses = obtenerEntero();

                std::cout << "Ingrese la tasa de interés anual: ";
                tasaInteres = obtenerDecimal();
            }

            // Validar fondos y crear CDP
            if (cuenta.solicitarCDP(db, moneda, monto, plazoMeses, tasaInteres)) {
                std::cout << "CDP solicitado exitosamente." << std::endl;
            } else {
                std::cerr << "Error: No se pudo solicitar el CDP." << std::endl;
            }
            break;
        }
        case OpcionesCDP::VER_ESTADO: {
            // Ver estado de un CDP
            std::cout << "Ingrese el ID del CDP: ";
            int idCDP = obtenerEntero();

            CDP cdp = CDP::obtener(db, idCDP);
            if (!cdp.getID()) {
                // Salir en caso de que no exista un CDP con el ID ingresado
                break;
            }

            cdp.mostrarInformacion(); // Invoca la función para mostrar datos del CDP
            break;
        }
        case OpcionesCDP::REGRESAR:
            std::cout << "Regresando al menú de operaciones." << std::endl;
            break;
        default:
            std::cout << "Opción inválida." << std::endl;
            break;
    }
}

// Manejar opciones de abono a préstamo
void manejarAbonoPrestamo(sqlite3* db, Cuenta& cuenta) {
    std::cout << "\n=== Abono a Préstamo ===" << std::endl;
    std::cout << "1. Abonar a un préstamo propio" << std::endl;
    std::cout << "2. Abonar a un préstamo de terceros" << std::endl;
    std::cout << "3. Regresar" << std::endl;
    std::cout << "Seleccione una opción: ";
    
    int opcionAbono = obtenerEntero();
    switch (static_cast<OpcionesAbono>(opcionAbono)) {
        case OpcionesAbono::PRESTAMO_PROPIO: {
            // Abonar a un préstamo propio
            std::cout << "Ingrese el ID del préstamo: ";
            int idPrestamo = obtenerEntero();

            // Buscar el préstamo actual en la base de datos
            Prestamo prestamo = Prestamo::obtener(db, idPrestamo);

            // Verificar que el préstamo sea válido
            if (prestamo.getID() == 0) {
                std::cerr << "Error: El préstamo no fue encontrado." << std::endl;
                break;
            }

            // Verificar que el préstamo pertenece a la cuenta actual
            if (prestamo.getIDCuenta() != cuenta.getID()) {
                std::cerr << "Error: El préstamo no pertenece a la cuenta actual." << std::endl;
                break;
            }

            prestamo.mostrarInformacionPago();

            // Confirmar el abono
            std::cout << "¿Desea realizar el abono de la cuota mensual? (s/n): ";
            bool confirmar = validarRespuestaSN();

            if (confirmar) {
                if (prestamo.abonarCuota(db, cuenta)) {
                    std::cout << "Abono realizado con éxito." << std::endl;
                } else {
                    std::cerr << "Error al realizar el abono." << std::endl;
                }
            } else {
                std::cout << "Abono cancelado por el usuario." << std::endl;
            }
            break;
        }
        case OpcionesAbono::PRESTAMO_TERCEROS: {
            // Abonar a un préstamo de terceros
            std::cout << "Ingrese el ID del préstamo: ";
            int idPrestamo = obtenerEntero();
            Prestamo prestamo = Prestamo::obtener(db, idPrestamo);

            // Validar préstamo
            if (prestamo.getID() == 0) {
                std::cerr << "Error: El préstamo no fue encontrado." << std::endl;
                break;
            }

            prestamo.mostrarInformacionPago();

            // Confirmar el abono
            std::cout << "¿Desea realizar el abono de la cuota mensual al préstamo de terceros? (s/n): ";
            bool confirmar = validarRespuestaSN();

            if (confirmar) {
                if (prestamo.abonarCuota(db, cuenta)) {
                    std::cout << "Abono realizado con éxito al préstamo de terceros." << std::endl;
                } else {
                    std::cerr << "Error al realizar el abono." << std::endl;
                }
            } else {
                std::cout << "Abono cancelado por el usuario." << std::endl;
            }
            break;
        }
        case OpcionesAbono::REGRESAR:
            std::cout << "Regresando al menú de operaciones." << std::endl;
            break;
        default:
            std::cout << "Opción inválida." << std::endl;
            break;
    }
}

// Realizar un depósito
void realizarDeposito(sqlite3* db, Cuenta& cuenta) {
    std::cout << "Ingrese monto a depositar: ";
    double montoDeposito = obtenerDecimal(); // Validar monto a depositar

    // Realizar transacción de depósito
    if (cuenta.depositar(db, montoDeposito)) {
        std::cout << "Depósito realizado con éxito." << std::endl;
    }
}

// Realizar una transferencia
void realizarTransferencia(sqlite3* db, Cuenta& cuenta) {
    std::cout << "Ingrese ID de la cuenta destino: ";
    int idCuentaDestino = obtenerEntero(); // Validar número de cuenta de destinatario
    
    // Obtener la cuenta de destino
    Cuenta cuentaDestino = Cuenta::obtener(db, idCuentaDestino);

    // Verificar que la cuenta existe
    if (cuentaDestino.getID() == 0) {
        std::cout << "Error: La cuenta destino no existe." << std::endl;
        return;
    }

    // Verificar compatibilidad de monedas entre cuenta remitente y destinatario
    if (!cuenta.verificarCompatibilidadMoneda(db, idCuentaDestino)) {
        std::cerr << "Error: Las cuentas deben ser de la misma moneda para realizar la transferencia." << std::endl;
        return;
    }

    // Ingreso de cédula de cliente de la cuenta destino
    std::cout << "Ingrese la cédula del titular de la cuenta destino: ";
    int cedulaDestino = obtenerEntero();

    // Obtener el cliente de destino
    Cliente clienteDestino = Cliente::obtener(db, cedulaDestino);

    // Verificar que el cliente existe y que idCliente coincide entre cliente y cuenta de destino
    if (clienteDestino.getID() == 0 || clienteDestino.getID() != cuentaDestino.getIDCliente()) {
        std::cout << "Error: La cédula no coincide con la cuenta destino ingresada." << std::endl;
        return;
    }

    // Ingreso de monto a transferir
    std::cout << "Ingrese monto a transferir: ";
    double montoTransferencia = obtenerDecimal(); // Validar monto a transferir

    // Realizar la transacción actual
    if (cuenta.transferir(db, idCuentaDestino, montoTransferencia)) {
        std::cout << "Transferencia realizada con éxito." << std::endl;
    } else {
        std::cerr << "Error al realizar la transferencia." << std::endl;
    }
}

// Realizar un retiro
void realizarRetiro(sqlite3* db, Cuenta& cuenta) {
    std::cout << "Ingrese monto a retirar: ";
    double montoRetiro = obtenerDecimal(); // Validar monto a retirar
    
    // Realizar la transacción
    if (cuenta.retirar(db, montoRetiro)) {
        std::cout << "Retiro realizado con éxito." << std::endl;
    }
}

// -------------------------------- Menú de atención al cliente --------------------------------

// Función principal para gestionar el menú de atención al cliente
void menuAtencionCliente(sqlite3* db) {
    int opcionAtencion;

    do {
        // Mostrar el menú de atención al cliente
        mostrarMenuAtencion();
        opcionAtencion = obtenerEntero();

        // Validar opción seleccionada
        switch (static_cast<MenuAtencionClienteOpciones>(opcionAtencion)) {
            case MenuAtencionClienteOpciones::INICIAR_SESION:
                iniciarSesionCliente(db);
                break;
            case MenuAtencionClienteOpciones::REGISTRAR_CLIENTE:
                registrarCliente(db);
                break;
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


// Mostrar el menú de atención al cliente
void mostrarMenuAtencion() {
    std::cout << "\n=== Menú de Atención al Cliente ===" << std::endl;
    std::cout << "1. Iniciar Sesión" << std::endl;
    std::cout << "2. Registrar Cliente" << std::endl;
    std::cout << "3. Regresar" << std::endl;
    std::cout << "Seleccione una opción: ";
}


// Iniciar sesión de cliente
void iniciarSesionCliente(sqlite3* db) {
    // Solicitud de cédula de identificación
    std::cout << "Ingrese la cédula del cliente: ";
    int cedula = obtenerEntero();

    // Verificar si existe un cliente con la cédula ingresada y obtener el ID de ese cliente
    Cliente cliente = Cliente::obtener(db, cedula);
    int idCliente = cliente.getID();

    // Si no existe, se sale y vuelve a mostrar el menú
    if (idCliente == 0) {
        return;
    }

    std::cout << "\n=== Ingreso a cuenta ===" << std::endl;
    std::cout << "1. Crear nueva cuenta" << std::endl;
    std::cout << "2. Acceder a cuenta existente" << std::endl;
    std::cout << "Seleccione una opción: ";

    // Opción respecto a la cuenta con la que desea iniciar sesión
    int opcionCuenta = obtenerEntero();

    // Clasificar opción de cuenta
    switch (static_cast<MenuCuentaOpciones>(opcionCuenta)) {
        case MenuCuentaOpciones::CREAR_CUENTA: {
            // Opción de crear cuenta

            // Ingreso del tipo de moneda de la cuenta
            std::string moneda = validarMoneda();

            // Ingreso del saldo inicial de la cuenta
            std::cout << "Ingrese saldo inicial: ";
            double saldoInicial = obtenerDecimal();

            // Ingreso de la tasa de interés de la cuenta
            std::cout << "Ingrese tasa de interés: ";
            double tasaInteres = obtenerDecimal();

            // Crear instancia de Cuenta con los datos ingresados (saldo inicial 0)
            Cuenta nuevaCuenta(idCliente, moneda, 0, tasaInteres);

            // Insertar en la base de datos
            if (nuevaCuenta.crear(db)) {
                std::cout << "Cuenta creada con éxito.\nID de la cuenta: " << nuevaCuenta.getID() << std::endl;
            }

            // Realizar el depósito del saldo inicial
            nuevaCuenta.depositar(db, saldoInicial);
            break;
        }
        case MenuCuentaOpciones::ACCEDER_CUENTA: {
            // Opción de acceder a una cuenta existente

            // Solicitud del identificador de la cuenta
            std::cout << "Ingrese el ID de la cuenta: ";
            int idCuenta = obtenerEntero();

            // Buscar cuenta con el ID ingresado
            Cuenta cuenta = Cuenta::obtener(db, idCuenta);

            // Comprobar que exista la cuenta y que la cuenta pertenezca al cliente actual
            if (cuenta.getID() == 0 || cuenta.getIDCliente() != idCliente) {
                std::cout << "Error: La cuenta no existe o no pertenece al cliente." << std::endl;
                return;
            }

            // Mostrar el menú de operaciones de la cuenta
            menuOperacionesCliente(db, cuenta);
            break;
        }
        case MenuCuentaOpciones::REGRESAR: {
            std::cout << "Regresando al menú de atención al cliente." << std::endl;
            break;
        }
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            break;
    }
}

// Registrar un nuevo cliente
void registrarCliente(sqlite3* db) {
    // Ingreso de cédula
    std::cout << "Ingrese cédula: ";
    int cedula = obtenerEntero();

    // Verificar que no exista un cliente registrado con el mismo número de cédula
    if (Cliente::existe(db, cedula)) {
        std::cout << "Error: El cliente ya está registrado." << std::endl;
        return;
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
}

// -------------------------------- Menú de préstamos --------------------------------

// Función principal para gestionar el menú de préstamos
void menuPrestamos(sqlite3* db) {
    int opcionPrestamo;
    do {
        // Mostrar el menú de préstamos
        mostrarMenuPrestamos();
        opcionPrestamo = obtenerEntero();

        switch (static_cast<MenuPrestamosOpciones>(opcionPrestamo)) {
            case MenuPrestamosOpciones::SOLICITAR_PRESTAMO:
                solicitarPrestamo(db);
                break;
            case MenuPrestamosOpciones::CONSULTAR_PRESTAMOS:
                consultarPrestamos(db);
                break;
            case MenuPrestamosOpciones::REGRESAR:
                std::cout << "Regresando al menú principal.\n";
                break;
            default:
                std::cerr << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    } while (opcionPrestamo != static_cast<int>(MenuPrestamosOpciones::REGRESAR));
}

// Mostrar el menú de préstamos
void mostrarMenuPrestamos() {
    std::cout << "\n=== Menú de Préstamos ===" << std::endl;
    std::cout << "1. Solicitar préstamo" << std::endl;
    std::cout << "2. Consultar préstamos" << std::endl;
    std::cout << "3. Regresar" << std::endl;
    std::cout << "Seleccione una opción: ";
}

// Solicitar un préstamo
void solicitarPrestamo(sqlite3* db) {
    std::cout << "\n=== Solicitar Préstamo ===" << std::endl;
    std::cout << "Seleccione el tipo de préstamo:" << std::endl;
    std::cout << "1. Personal" << std::endl;
    std::cout << "2. Prendario" << std::endl;
    std::cout << "3. Hipotecario" << std::endl;
    std::cout << "Opción: ";

    int tipoSeleccionado = obtenerEntero();
    std::string tipoPrestamo;

    if (tipoSeleccionado == static_cast<int>(TipoPrestamo::PERSONAL))
        tipoPrestamo = "PER";
    else if (tipoSeleccionado == static_cast<int>(TipoPrestamo::PRENDARIO))
        tipoPrestamo = "PRE";
    else if (tipoSeleccionado == static_cast<int>(TipoPrestamo::HIPOTECARIO))
        tipoPrestamo = "HIP";
    else {
        std::cout << "Error: Tipo de préstamo inválido. Regresando al menú de préstamos." << std::endl;
        return;
    }

    // Variables para almacenar los datos de creación del préstamo
    double monto, tasaInteres, cuotaMensual;
    int plazoMeses;

    // Selección de moneda
    std::string moneda = validarMoneda();

    // Mostrar valores predeterminados
    struct ValoresPrestamo valoresPrestamo = Prestamo::obtenerValoresPredeterminados(static_cast<TipoPrestamo>(tipoSeleccionado), moneda);

    // Verificar que sea un struct válido
    if (valoresPrestamo.monto == 0.0) {
        std::cerr << "Error: Tipo de préstamo no válido" << std::endl;
        return;
    } 

    std::cout << "\nValores predeterminados para el préstamo seleccionado:" << std::endl;
    std::cout << "Monto: " << valoresPrestamo.monto << std::endl;
    std::cout << "Plazo (meses): " << valoresPrestamo.plazoMeses << std::endl;
    std::cout << "Tasa de interés (%): " << valoresPrestamo.tasaInteres << std::endl;
    std::cout << "Cuota mensual estimada: " << valoresPrestamo.cuotaMensual << std::endl;

    // Preguntar si se desea modificar
    std::cout << "¿Desea modificar los valores predeterminados? (s/n): ";
    bool modificar = validarRespuestaSN();

    if (modificar) {
        std::cout << "Ingrese el monto del préstamo: ";
        monto = obtenerDecimal();

        std::cout << "Ingrese el plazo en meses: ";
        plazoMeses = obtenerEntero();

        std::cout << "Ingrese la tasa de interés (%): ";
        tasaInteres = obtenerDecimal();

        cuotaMensual = Prestamo::calcularCuotaMensual(monto, tasaInteres, plazoMeses);
    } else {
        monto = valoresPrestamo.monto;
        plazoMeses = valoresPrestamo.plazoMeses;
        tasaInteres = valoresPrestamo.tasaInteres;
        cuotaMensual = valoresPrestamo.cuotaMensual;
    }

    // Generar reporte estimado
    Prestamo prestamo(0, tipoPrestamo, moneda, monto, tasaInteres, plazoMeses, cuotaMensual);
    prestamo.reportePagoEstimado(moneda, monto, plazoMeses, tasaInteres, cuotaMensual);

    // Preguntar si se desea solicitar el préstamo
    std::cout << "¿Desea solicitar este préstamo? (s/n): ";
    bool solicitar = validarRespuestaSN();

    if (solicitar) {
        std::cout << "Ingrese la cédula del cliente: ";
        int cedula = obtenerEntero();

        Cliente cliente = Cliente::obtener(db, cedula);
        if (cliente.getID() == 0) {
            std::cerr << "Error: El cliente no existe." << std::endl;
            return;
        }

        std::cout << "Ingrese el ID de la cuenta asociada al préstamo: ";
        int idCuenta = obtenerEntero();
        Cuenta cuenta = Cuenta::obtener(db, idCuenta);

        if (cuenta.getID() == 0 || cuenta.getIDCliente() != cliente.getID()) {
            std::cerr << "Error: La cuenta no existe o no pertenece al cliente." << std::endl;
            return;
        }

        if (cuenta.getMoneda() != moneda) {
            std::cerr << "Error: La cuenta no coincide con la moneda indicada." << std::endl;
            return;
        }

        prestamo.setIDCuenta(idCuenta);

        if (prestamo.crear(db)) {
            std::cout << "Préstamo solicitado con éxito." << std::endl;
        }
    } else {
        std::cout << "Solicitud de préstamo cancelada." << std::endl;
    }
}


// Consultar préstamos
void consultarPrestamos(sqlite3* db) {
    std::cout << "Ingrese el ID del préstamo que desea consultar: ";
    int idPrestamo = obtenerEntero();

    // Preguntar si desea generar un archivo
    std::cout << "¿Desea generar un archivo (.csv) con el estado del préstamo? (s/n): ";
    bool generarReporte = validarRespuestaSN();

    std::string nombreArchivo = "";
    if (generarReporte) {
        std::cout << "Ingrese el nombre del archivo: ";
        nombreArchivo = obtenerArchivoCSV();
    }

    // Consultar el estado del préstamo y generar reporte si corresponde
    if (!Prestamo::consultarEstado(db, idPrestamo, nombreArchivo)) {
        std::cerr << "Error: No se pudo consultar el estado del préstamo.\n";
    }
}