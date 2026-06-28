#include "sqlite_connection.hpp"

SQLiteConnection::SQLiteConnection(const std::string& path) : connection_(nullptr), path_(path) {
    if (sqlite3_open(path_.c_str(), &connection_) != SQLITE_OK) {
        throw std::runtime_error("Nao foi possivel abrir o banco de dados SQLite.");
    }
}

SQLiteConnection::~SQLiteConnection() {
    if (connection_ != nullptr) {
        sqlite3_close(connection_);
    }
}

void SQLiteConnection::execute(const std::string& sql) {
    char* errorMessage = nullptr;
    if (sqlite3_exec(connection_, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::string message = errorMessage ? errorMessage : "Erro desconhecido do SQLite.";
        sqlite3_free(errorMessage);
        throw std::runtime_error("Erro ao executar comando SQLite: " + message);
    }
}

std::vector<std::vector<std::string>> SQLiteConnection::query(const std::string& sql) const {
    std::vector<std::vector<std::string>> rows;
    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(connection_, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta SQLite.");
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        std::vector<std::string> row;
        int columnCount = sqlite3_column_count(statement);
        for (int i = 0; i < columnCount; ++i) {
            const unsigned char* value = sqlite3_column_text(statement, i);
            row.emplace_back(value ? reinterpret_cast<const char*>(value) : "");
        }
        rows.push_back(std::move(row));
    }

    sqlite3_finalize(statement);
    return rows;
}
