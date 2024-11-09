

#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP

#include <iostream>

std::string validarFecha();

int obtenerEntero();

double obtenerDecimal();

std::string validarMoneda();

std::string validarTelefono();

/// @brief Función para calcular el resultado de elevar un numero a una potencia
/// @param n Numero que se quiere elevar
/// @param p Potencia
/// @return Resultado de la operación
double potencia(double n, double p);

/// @brief Función para calcular la cuota mensula a pagar para un préstamo
/// @param monto Monto del préstamo
/// @param plazo Plazo del préstamo
/// @param tasaInteres Tasa de interés del préstamo
/// @return Monto de la cuota mensual
double calcularCuotaMensual(double monto, int plazo, double tasaInteres);


#endif // AUXILIARES_HPP