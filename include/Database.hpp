

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <sqlite3.h>

/**
 * @brief Clase que gestiona la conexión a la base de datos.
 * 
 * Esta clase permite abrir y cerrar la conexión a la base de datos SQLite.
 */
class Database {
    private:
        sqlite3* db; /**< Puntero a la conexión de base de datos SQLite */

    public:
        /**
         * @brief Constructor de la clase Database.
         * 
         * Inicializa y abre la conexión a la base de datos especificada.
         * 
         * @param dbName Nombre de la base de datos a abrir.
         */
        Database(const std::string& dbName);
        
        /**
         * @brief Destructor de la clase Database.
         * 
         * Cierra la conexión a la base de datos al destruir el objeto.
         */
        ~Database();
};

#endif // DATABASE_HPP
