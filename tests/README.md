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

### `menuOperacionesCliente`

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### `menuAtencionCliente`

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### `menuPrestamos`

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


## Pruebas de Métodos Individuales

### Ver Saldo
- **Caso 1:** Cuenta inexistente → Mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Caso 2:** Cuenta existente → Mostrar saldo correctamente.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### Consultar Historial
- **Caso 1:** Cuenta inexistente → Mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Caso 2:** Cuenta existente → Mostrar historial de transacciones.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### CDPs
- **Ver CDP inexistente:** Debe mostrar un mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Ver CDP existente:** Debe mostrar los datos del CDP.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Crear CDP:**
  - **Parámetros válidos:** Debe crear el CDP correctamente.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


  - **Parámetros inválidos:** Debe manejar el error y mostrar el mensaje correspondiente.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### Abonos a Préstamos
- **Propios:**
  - **Parámetros válidos:** Abono exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

  - **Parámetros inválidos:** Manejo de errores.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **De terceros:**
  - **Parámetros válidos:** Abono exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


  - **Fondos insuficientes:** Mostrar mensaje de error.


<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### Depósitos
- **Cuenta inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Cuenta existente:** Depósito exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>



### Transferencias
- **Cuenta remitente inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Cuenta destinatario inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Fondos insuficientes:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### Retiros
- **Fondos insuficientes:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Cuenta inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Cuenta existente:** Retiro exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### Atención al Cliente
- **Registrar cliente existente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Registrar cliente nuevo:** Registro exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Iniciar sesión con cliente inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


- **Iniciar sesión con cliente existente:** Inicio de sesión exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>


### Cuentas
- **Crear cuenta con moneda existente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

- **Crear cuenta con moneda nueva:** Creación exitosa.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

- **Acceder a cuenta inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

- **Acceder a cuenta existente:** Acceso exitoso.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

### Solicitud de Préstamos
- **Menú de tipo de préstamo:** Validación correcta de opciones.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

- **Generación de tabla de pago estimado:** Mostrar datos correctos.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

- **Cancelación de solicitud:** Proceso cancelado correctamente.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

### Consulta de Préstamos
- **Préstamo inexistente:** Mostrar mensaje de error.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>

- **Generación de reportes en archivo .csv:** Archivo generado correctamente.

<p align="center">
  <img width="750" src="./images/>

  __Figura X.__ xxxx.
</p>



