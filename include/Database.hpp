/**
 * @file Database.hpp
 * @brief Declaración de la clase Database para gestionar la conexión a la base de datos.
 * @details Este archivo contiene la declaración de la clase Database, que facilita la gestión
 *          de la conexión a una base de datos SQLite, permitiendo abrir y cerrar la conexión
 *          de forma segura.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @date 08/11/2024
 * @copyright MIT License
 */

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <sqlite3.h>

/**
 * @brief Clase que gestiona la conexión a la base de datos.
 * 
 * Esta clase permite abrir y cerrar la conexión a la base de datos SQLite. 
 * Al crear un objeto de esta clase, se abre la conexión, y al destruir el objeto, 
 * la conexión se cierra automáticamente.
 */
class Database {
    private:
        /// @brief Puntero a la conexión de base de datos SQLite.
        sqlite3* db;

    public:
        /**
         * @brief Constructor de la clase Database.
         * 
         * Inicializa y abre la conexión a la base de datos especificada. Si no se puede
         * abrir la base de datos, el constructor maneja el error apropiadamente.
         * 
         * @param dbName Nombre de la base de datos a abrir.
         */
        Database(const std::string& dbName);
        
        /**
         * @brief Destructor de la clase Database.
         * 
         * Cierra la conexión a la base de datos al destruir el objeto, liberando los recursos
         * utilizados.
         */
        ~Database();

        /**
         * @brief Retorna un puntero a la conexión de la base de datos en SQLite
         * 
         * @return `sqlite3*` Puntero a la conexión
         */
        sqlite3* get() const;
};

#endif // DATABASE_HPP
