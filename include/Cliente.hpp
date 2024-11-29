/**
 * @file Cliente.hpp
 * @brief Declaración de la clase Cliente para gestionar datos de clientes en la base de datos.
 * @details Este archivo define la estructura y métodos de la clase Cliente, que permite crear,
 *          obtener y verificar la existencia de clientes en la base de datos. Los métodos de
 *          esta clase incluyen funcionalidades para manipular y consultar la información básica
 *          de los clientes, como cédula, nombre, apellidos y teléfono.

 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <sqlite3.h>

/**
 * @brief Clase que representa a un cliente en el sistema.
 * 
 * La clase Cliente contiene información personal del cliente, como cédula, nombre, apellidos 
 * y teléfono.
 * Proporciona métodos para crear y obtener clientes desde la base de datos, 
 * así como para verificar si un cliente existe en el sistema.
 */
class Cliente {
    private:
        /// @brief Identificador único del cliente en la base de datos.
        int idCliente = 0;

        /// @brief Número de cédula del cliente.
        int cedula;

        /// @brief Nombre del cliente.
        std::string nombre;

        /// @brief Primer apellido del cliente.
        std::string primerApellido;

        /// @brief Segundo apellido del cliente.
        std::string segundoApellido;

        /// @brief Número de teléfono del cliente.
        std::string telefono;

    public:
        /**
         * @brief Constructor para inicializar un cliente con datos específicos.
         * @param cedula Número de cédula del cliente.
         * @param nombre Nombre del cliente.
         * @param primerApellido Primer apellido del cliente.
         * @param segundoApellido Segundo apellido del cliente.
         * @param telefono Número de teléfono del cliente.
         */
        Cliente(int cedula, const std::string &nombre, const std::string &primerApellido, const std::string &segundoApellido, const std::string &telefono);
  
        /**
         * @brief Crea un nuevo registro de cliente en la base de datos.
         * 
         * Verifica si el cliente ya existe mediante su cédula. Si no existe,
         * inserta un nuevo registro en la base de datos con los datos del cliente.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @return `true` si la creación fue exitosa, `false` en caso contrario.
         */
        bool crear(sqlite3* db);

        /**
         * @brief Obtiene un cliente desde la base de datos a partir de su cédula.
         * 
         * Realiza una consulta en la base de datos para buscar un cliente con la
         * cédula especificada. Si se encuentra, retorna un cliente con los datos 
         * correspondientes; en caso contrario, retorna un cliente vacío.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param cedula Número de cédula del cliente a buscar.
         * @return Objeto Cliente con los datos obtenidos, o vacío si no se encontró.
         */
        static Cliente obtener(sqlite3* db, int cedula);

        /**
         * @brief Verifica si un cliente existe en la base de datos.
         * 
         * Comprueba si un cliente con la cédula especificada ya existe en el sistema
         * mediante una consulta a la base de datos.
         * 
         * @param db Conexión a la base de datos SQLite.
         * @param cedula Número de cédula del cliente a verificar.
         * @return `true` si el cliente existe, `false` en caso contrario.
         */
        static bool existe(sqlite3* db, int cedula);

        /**
         * @brief Retorna la cédula del cliente.
         * 
         * @return `int` cédula
         */
        int getCedula() const;

        /**
         * @brief Retorna el identificador del cliente (ID)
         * 
         * @return `int` idCliente
         */
        int getID() const;

};

#endif // CLIENTE_HPP