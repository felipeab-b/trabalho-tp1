#ifndef SQLITE_CONNECTION_HPP
#define SQLITE_CONNECTION_HPP

#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>

class SQLiteConnection {
public:
    explicit SQLiteConnection(const std::string& path);
    ~SQLiteConnection();

    void execute(const std::string& sql);
    std::vector<std::vector<std::string>> query(const std::string& sql) const;

private:
    sqlite3* connection_;
    std::string path_;
};

#endif
