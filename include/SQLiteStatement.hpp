/**
 * @file SQLiteStatement.hpp
 * @brief Clase para manejar declaraciones preparadas de SQLite.
 * @details Esta clase facilita la gestión de sentencias SQL preparadas en SQLite, proporcionando
 *          un manejo seguro y eficiente de recursos.
 *          Permite preparar, ejecutar y liberar automáticamente las sentencias SQL, evitando fugas de memoria.
 * 
 * @author Daniel Alberto Sáenz Obando
 * @author Rodrigo Madrigal Montes
 * @copyright MIT License
 * @date 28/11/2024
 */

#ifndef SQLITE_STATEMENT_H
#define SQLITE_STATEMENT_H

#include <sqlite3.h>
#include <string>

/**
 * @class SQLiteStatement
 * @brief Encapsula el manejo de declaraciones preparadas en SQLite.
 * 
 * Esta clase facilita la preparación y gestión de sentencias SQL en una base de datos SQLite,
 * asegurando que los recursos se liberen correctamente.
 */
class SQLiteStatement {
    public:
        /**
         * @brief Constructor de la clase SQLiteStatement.
         * 
         * Prepara una declaración SQL para la base de datos especificada.
         * 
         * @param db Puntero a la base de datos SQLite.
         * @param query Consulta SQL a preparar.
         */
        SQLiteStatement(sqlite3* db, const std::string& query);

        /**
         * @brief Destructor de la clase SQLiteStatement.
         * 
         * Libera los recursos asociados con la declaración preparada.
         */
        ~SQLiteStatement();

        /**
         * @brief Obtiene el puntero a la declaración preparada.
         * 
         * Permite acceder a la declaración preparada para su ejecución.
         * 
         * @return Puntero a la declaración preparada (`sqlite3_stmt*`).
         */
        sqlite3_stmt* get() const;

    private:
        /// @brief Puntero a la declaración preparada de SQLite.
        sqlite3_stmt* stmt_;
};

#endif // SQLITE_STATEMENT_H