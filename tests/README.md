# Pruebas del Sistema de Gestión Bancaria

Este documento detalla las pruebas realizadas en el sistema de gestión bancaria, incluyendo pruebas a los menús y métodos individuales. Se describen los casos de prueba, los resultados esperados y las observaciones relevantes.


## Índice

1. [Pruebas de Menús](#pruebas-de-menús)
2. [Pruebas de Métodos Individuales](#pruebas-de-métodos-individuales)
   - [Ver Saldo](#ver-saldo)
   - [Consultar Historial](#consultar-historial)
   - [CDPs](#cdps)
   - [Abonos a Préstamos](#abonos-a-préstamos)
   - [Depósitos](#depósitos)
   - [Transferencias](#transferencias)
   - [Retiros](#retiros)
   - [Atención al Cliente](#atención-al-cliente)
   - [Cuentas](#cuentas)
   - [Solicitud de Préstamos](#solicitud-de-préstamos)
   - [Consulta de Préstamos](#consulta-de-préstamos)


## Pruebas de Menús

**Descripción:**  
Se realizaron pruebas para verificar el manejo de entradas inválidas en los menús utilizando funciones auxiliares de validación.

**Resultados esperados:**  
Los menús deben manejar correctamente entradas inválidas y guiar al usuario a ingresar datos válidos.

### `menuPrincipal`

<div align="center">

| ![menuPrincipal*](/images/1.0.png) |
|:--:|
| *menuPrincipal* |

</div>


### `menuOperacionesCliente`

<div align="center">

| ![menuOperacionesCliente*](/images/2.0.png) |
|:--:|
| *menuOperacionesCliente* |

</div>

### `menuAtencionCliente` ingreso exitoso

<div align="center">

| ![menuAtencionCliente exitoso*](/images/1.1.png) |
|:--:|
| *menuAtencionCliente exitoso* |

</div>


### `menuAtencionCliente` ingreso fallido

<div align="center">

| ![menuAtencionCliente fallido*](/images/1.3.png) |
|:--:|
| *menuAtencionCliente fallido* |

</div>

### `menuPrestamos`

<div align="center">

| ![menuPrestamos*](/images/1.4.png) |
|:--:|
| *menuPrestamos* |

</div>


## Pruebas de Métodos Individuales

### Ver Saldo
- **Caso 1:** Cuenta inexistente → Mensaje de error.

<div align="center">

| ![*](/images/2.1.png) |
|:--:|
|  |

</div>


- **Caso 2:** Cuenta existente → Mostrar saldo correctamente.

<div align="center">

| ![*](/images/2.2.png) |
|:--:|
|  |

</div>


### Consultar Historial

- **Caso** Cuenta existente → Mostrar historial de transacciones.

<div align="center">

| ![*](/images/3.2.png) |
|:--:|
|  |

</div>


### CDPs

- **Mostrar menú de CDP:** 

<div align="center">

| ![*](/images/4.0.png) |
|:--:|
|  |

</div>

- **Ver CDP inexistente:** Debe mostrar un mensaje de error.

<div align="center">

| ![*](/images/4.1.png) |
|:--:|
|  |

</div>


- **Ver CDP existente:** Debe mostrar los datos del CDP.

<div align="center">

| ![*](/images/4.2.png) |
|:--:|
|  |

</div>


- **Crear CDP:**
  - **Parámetros válidos:** Debe crear el CDP correctamente y avisando de los errores en el formato de entrada en caso de que se de la situación.

<div align="center">

| ![*](/images/4.3.png) |
|:--:|
|  |

</div>

Se muestran las imagenes de la tabla de `CDP` antes y despues de la creación del CDP anterior:

<div align="center">

| ![Tabla de CDP antes de la creación del nuevo*](/images/tablaCDPsOriginal.png) |
|:--:|
| *Tabla de CDP antes de la creación del nuevo* |

</div>

<div align="center">

| ![Tabla de CDP despues de la creación del nuevo*](/images/tablaCDPsNuevoCDP.png) |
|:--:|
| *Tabla de CDP despues de la creación del nuevo* |

</div>

### Abonos a Préstamos
- **Propios:**

  - **Parámetros inválidos:** Manejo de errores.

<div align="center">

| ![*](/images/5.1.png) |
|:--:|
|  |

</div>

- **De terceros:**
  - **Parámetros válidos:** Abono exitoso.

<div align="center">

| ![*](/images/5.4.png) |
|:--:|
|  |

</div>


Se muestran imagenes para demostrar que se generó un registro del abono al préstamo en la tabla de `PagoPrestamos`:

<div align="center">

| ![Tabla de PagoPrestamos antes del abono*](/images/tablaPagoPrestamosOriginal.png) |
|:--:|
| *Tabla de PagoPrestamos antes del abono* |

</div>

<div align="center">

| ![Tabla de PagoPrestamos despues del abono*](/images/tablaPagoPrestamosNuevoPrestamo.png) |
|:--:|
| *Tabla de PagoPrestamos despues del abono* |

</div>



</div>

  - **Parámetros inválidos:** Abono fallido.

<div align="center">

| ![*](/images/5.3.png) |
|:--:|
|  |

</div>


### Depósitos
- **Cuenta inexistente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/6.1.png) |
|:--:|
|  |

</div>


- **Cuenta existente:** Depósito exitoso.

<div align="center">

| ![*](/images/6.2.png) |
|:--:|
|  |

</div>

Se adjunta imagen para mostrar creación de registro en la tabla `Transacciones` al realizar el depósito anterior:

<div align="center">

| ![*](/images/tablaTransaccionesDeposito.png) |
|:--:|
|  |

</div>


### Transferencias

- **Cuenta destinatario inexistente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/7.2.png) |
|:--:|
|  |

</div>


- **Fondos insuficientes:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/7.3.png) |
|:--:|
|  |

</div>

- **Transferencia exitosa:** 

<div align="center">

| ![*](/images/7.4.png) |
|:--:|
|  |

</div>

### Retiros
- **Fondos insuficientes:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/8.1.png) |
|:--:|
|  |

</div>


- **Cuenta existente:** Retiro exitoso.

<div align="center">

| ![*]() |
|:--:|
|  |

</div>


### Atención al Cliente
- **Registrar cliente existente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/9.1.png) |
|:--:|
|  |

</div>


- **Registrar cliente nuevo:** Registro exitoso.

<div align="center">

| ![*](/images/2.3.png) |
|:--:|
|  |

</div>

Se muestran imagenes que demuestran que se generó exitosamente un nuevo registro en la tabla de clientes:

<div align="center">

| ![Tabla de Cliente antes de la creación del nuevo*](/images/tablaClientesOriginal.png) |
|:--:|
| *Tabla de Cliente antes de la creación del nuevo* |

</div>

<div align="center">

| ![Tabla de Cliente despues de la creación del nuevo*](/images/tablaClienteNuevoCliente.png) |
|:--:|
| *Tabla de Cliente despues de la creación del nuevo* |

</div>

- **Iniciar sesión con cliente inexistente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/9.3.png) |
|:--:|
|  |

</div>

- **Iniciar sesión con cliente existente:** Inicio de sesión exitoso.

<div align="center">

| ![*](/images/9.4.png) |
|:--:|
|  |

</div>


### Cuentas
- **Crear cuenta con moneda existente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/10.1.png) |
|:--:|
|  |

</div>

- **Crear cuenta con moneda nueva:** Creación exitosa.

<div align="center">

| ![*](/images/2.4.png) |
|:--:|
|  |

</div>

Se muestran imagenes para demostrar que se creó exitosamente un registro de una nueva cuenta en la tabla de Cuentas:

<div align="center">

| ![Tabla de Cuentas antes de la creación de la nueva*](/images/tablaCuentasOriginal.png) |
|:--:|
| *Tabla de Cuentas antes de la creación de la nueva* |

</div>

<div align="center">

| ![Tabla de Cuentas despues de la creación de la nueva*](/images/tablaCuentaNuevaCuenta.png) |
|:--:|
| *Tabla de Cuentas despues de la creación de la nueva* |

</div>

- **Acceder a cuenta inexistente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/10.3.png) |
|:--:|
|  |

</div>

- **Acceder a cuenta existente:** Acceso exitoso.

<div align="center">

| ![*](/images/10.4.png) |
|:--:|
|  |

</div>

### Solicitud de Préstamos
- **Menú de tipo de préstamo:** Validación correcta de opciones.

<div align="center">

| ![*](/images/11.1.png) |
|:--:|
|  |

</div>

- **Generación de tabla de pago estimado:** Mostrar datos correctos.

<div align="center">

| ![*](/images/11.2.png) |
|:--:|
|  |

</div>

- **Generación de reporte de solicitud en formato .csv**:

<div align="center">

| ![*](/images/11.3.1.png) |
|:--:|
|  |

</div>

<div align="center">

| ![*](/images/11.3.2.png) |
|:--:|
|  |

</div>

- **Cancelación de solicitud:** Proceso cancelado correctamente.

<div align="center">

| ![*](/images/11.4.png) |
|:--:|
|  |

</div>


Se muestran imagenes que demuestran la generación de un nuevo préstamo cuando se decide que si se quiere crearlo:

<div align="center">

| ![Tabla de Prestamos antes de la creación del nuevo*](/images/tablaPrestamosOriginal.png) |
|:--:|
| *Tabla de Prestamos antes de la creación del nuevo* |

</div>

<div align="center">

| ![Tabla de Prestamos despues de la creación del nuevo*](/images/11.6.png) |
|:--:|
| *Tabla de Prestamos despues de la creación del nuevo* |

</div>

### Consulta de Préstamos
- **Préstamo inexistente:** Mostrar mensaje de error.

<div align="center">

| ![*](/images/12.1.png) |
|:--:|
|  |

</div>

- **Generación de reportes en archivo .csv:** Archivo generado correctamente.

<div align="center">

| ![*](/images/12.2.1.png) |
|:--:|
|  |

</div>

<div align="center">

| ![*](/images/12.2.2.png) |
|:--:|
|  |

</div>


