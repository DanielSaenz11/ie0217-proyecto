# Archivos incluidos en el directorio `include/`

En este directorio están contenidos todos los archivos de encabezado de las clases, métodos y otras funciones implementadas en el programa del Sistema de Gestión Bancaria. A continuación se brinda un resumen y explicación de cuales son los contenidos de cada uno de estos archivos:

## `CDP.hpp`

Declaración de la clase `CDP` con sus atributos correspondientes, el constructor de la misma, el método `crear` para crear un CDP en la base de datos y el método `obtener` para mostrar los datos de un CDP de la base de datos. 

## `Cliente.hpp`

Declaración de la clase `Cliente` con sus atributos correspondientes, el constructor de la clase, el método `crear` para crear un cliente en la base de datos y el método `obtener` para obtener un cliente de la base de datos, método `existe` para verificar la existencia de un cliente y los métodos `getCedula` y `getID` para obetener la cédula y el ID de un cliente respectivamente.

## `Cuenta.hpp`

Declaración de la clase Cuenta con sus atributos correspondientes, el constructor de la clase, y los siguientes métodos:

- `crear`: Crea un nuevo registro de cuenta en la base de datos.
- `obtener`: Recupera una cuenta específica desde la base de datos usando su identificador.
- `existe`: Verifica si una cuenta existe en la base de datos.
- `getID`: Devuelve el identificador único de la cuenta.
- `getIDCliente`: Retorna el identificador del cliente asociado a la cuenta.
- `verSaldo`: Consulta el saldo actual de la cuenta.
- `depositar`: Realiza un depósito en la cuenta y actualiza el saldo en la base de datos.
- `retirar`: Realiza un retiro de la cuenta si hay fondos suficientes.
- `transferir`: Transfiere fondos a otra cuenta si ambas tienen la misma moneda.
- `abonarPrestamo`: Permite realizar un abono a un préstamo desde la cuenta.
- `solicitarCDP`: Solicita un Certificado de Depósito a Plazo, disminuyendo el saldo de la cuenta.
- `consultarHistorial`: Consulta y muestra el historial de transacciones de la cuenta.
- `actualizarSaldo`: Modifica el saldo de la cuenta en la base de datos.
- `existeSegunMoneda`: Verifica si existe una cuenta con la misma moneda para el cliente.
- `verificarFondos`: Comprueba que el saldo sea suficiente para una operación.
- `crearTransaccion`: Inserta un registro de transacción en la base de datos.
- `verificarCompatibilidadMoneda`: Asegura la compatibilidad de moneda para transferencias entre cuentas

## `Database.hpp`

Declaración de la clase Database con los siguientes elementos:

- `Constructor`: Inicializa y abre la conexión a la base de datos especificada.
- `Destructor`: Cierra la conexión a la base de datos al destruir el objeto.
- `get`: Retorna un puntero a la conexión de la base de datos SQLite.

## `Menu.hpp`

Declaración de funciones para la gestión de los menús del programa:
- `mostrarMenuPrincipal`: Despliega el menú principal, permitiendo al usuario seleccionar entre opciones de atención al cliente, información sobre préstamos bancarios o salir de la aplicación.
- `menuAtencionCliente`: Permite la interacción en el menú de atención al cliente, donde el usuario puede iniciar sesión con un cliente existente o registrar uno nuevo en la base de datos.
- `menuOperacionesCliente`: Permite realizar diversas operaciones para un cliente autenticado, incluyendo ver saldo, consultar historial de transacciones, solicitar un CDP, realizar abonos a préstamos, depósitos, transferencias y retiros.

## `PagoPrestamo.hpp`

Declaración de funciones para la gestión del pago de un préstamo, es decir cuando se realizan abonos a este:

- `Constructor`: Crea una instancia de la clase PagoPrestamo inicializando sus atributos: ID del préstamo asociado, cuota pagada, aportes al capital e intereses, y saldo restante tras el pago.

- `crear`: Registra un nuevo pago de préstamo en la base de datos. Devuelve un valor booleano que indica si el registro fue exitoso o no.

## `Prestamo.hpp`

Declaración de la clase Prestamo con sus atributos correspondientes, el constructor de la clase, y los siguientes métodos:

- `calcularCuotaMensual`
Realiza el cálculo de la cuota mensual del préstamo considerando el monto del préstamo, la tasa de interés y el plazo en meses. Este método es interno y no se accede desde fuera de la clase.

- `crear`: Registra el préstamo en la base de datos. Devuelve true si la operación fue exitosa y false en caso contrario.

- `obtener`:  Recupera los datos de un préstamo específico desde la base de datos utilizando su ID y devuelve una instancia de la clase Prestamo con esos datos.

- `existe`:  Verifica la existencia de un préstamo en la base de datos mediante su ID. Devuelve true si el préstamo existe y false si no.

## `SQLiteStatement.hpp`

Declaración de la clase `SQLiteStatement` para gestionar los *statement* para las consultas SQL implementadas en el programa para asegurar que no ocurran *memory leaks* u otros errores al momento de accederlos y manipularlos, este archivo incluye:

- `Constructor`: Crea una instancia de `SQLiteStatement` y prepara una sentencia SQL a partir de la base de datos `db` y la consulta query. Gestiona la creación del objeto `sqlite3_stmt`.

- `Destructor`: Libera los recursos asociados con la sentencia preparada, asegurando el cierre adecuado del objeto `sqlite3_stmt`.

- `get`: Devuelve un puntero al objeto `sqlite3_stmt`, permitiendo acceder a la sentencia preparada para su ejecución o evaluación.

## `Transaccion.hpp`

`Transaccion.hpp`: Declaración de la clase Transaccion para gestionar operaciones financieras:
- Atributos:
    - `idRemitente`: ID de la cuenta remitente.
    - `idDestinatario`: ID de la cuenta destinataria.
    - `tipo`: Tipo de transacción (DEP para depósito, RET para retiro, TRA para transacción, ABO para abono, CDP para certificado de depósito a plazo).
    - `monto`: Monto de la transacción.
- Métodos:
    - `Transaccion`: Constructor que inicializa una transacción con el remitente, destinatario, tipo de operación y monto.
    - `procesar`: Ejecuta la transacción en la base de datos, registrando los detalles y, dependiendo del tipo, modifica los saldos de las cuentas involucradas. Retorna true si la operación es exitosa o false en caso de error.

## `auxiliares.hpp`

Declaración de funciones auxiliares para validación y cálculos básicos:
- `validarFecha`: Solicita una fecha al usuario en formato YYYY-MM-DD y verifica que cumpla con el formato y los límites de días y meses.
- `obtenerEntero`: Solicita un número entero positivo al usuario, validando que la entrada sea válida.
- `obtenerDecimal`: Solicita un número decimal positivo al usuario, validando la entrada.
- `validarMoneda`: Presenta opciones de moneda al usuario (USD ó CRC) y valida la selección.
- `validarTelefono`: Solicita un número de teléfono en el formato (####-####) y verifica que cumpla con el formato.
- `potencia`: Calcula la potencia de un número base elevado a un exponente entero positivo (n^p).

## `constants.hpp`

Declaración de enumeraciones que representan las opciones en los diferentes menús de la aplicación:
- `MenuPrincipalOpciones`: Enumera las opciones del menú principal de la aplicación:
    - `ATENCION_CLIENTE`: Ir al menú de atención al cliente.
    - `PRESTAMO_BANCARIO`: Acceder a información sobre préstamos bancarios.
    - `SALIR`: Salir de la aplicación.
- `MenuAtencionClienteOpciones`: Enumera las opciones del menú de atención al cliente:
    - `INICIAR_SESION`: Iniciar sesión con un cliente existente.
    - `REGISTRAR_CLIENTE`: Registrar un nuevo cliente.
    - `REGRESAR`: Regresar al menú principal.
- `OperacionesCliente`: Enumera las opciones del menú de operaciones para un cliente autenticado:
    - `VER_SALDO`: Ver el saldo de la cuenta.
    - `CONSULTAR_HISTORIAL`: Consultar el historial de transacciones.
    - `SOLICITAR_CDP`: Solicitar un Certificado de Depósito a Plazo (CDP).
    - `ABONO_PRESTAMO`: Realizar un abono a un préstamo.
    - `DEPOSITO`: Realizar un depósito en la cuenta.
    - `TRANSFERENCIA`: Realizar una transferencia a otra cuenta.
    - `RETIRO`: Retirar fondos de la cuenta.
    - `REGRESAR`: Regresar al menú de selección de cuenta.

