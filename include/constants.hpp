

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Enum para las opciones del menú principal
enum class MenuPrincipalOpciones {
    ATENCION_CLIENTE = 1,
    PRESTAMO_BANCARIO,
    SALIR
};

// Enum para las opciones del menú de atención al cliente
enum class MenuAtencionClienteOpciones {
    INICIAR_SESION = 1,
    REGISTRAR_CLIENTE,
    REGRESAR
};

// Enum para las operaciones en el menú de cliente autenticado
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
