

#ifndef SQLITE_STATEMENT_H
#define SQLITE_STATEMENT_H

#include <sqlite3.h>
#include <string>

class SQLiteStatement {
    public:
        
        // Constructor
        SQLiteStatement(sqlite3* db, const std::string& query);

        // Destructor
        ~SQLiteStatement();

        // Getter
        sqlite3_stmt* get() const;

    private:
        sqlite3_stmt* stmt_;
};

#endif // SQLITE_STATEMENT_H