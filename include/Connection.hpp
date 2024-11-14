#pragma once
#include <pqxx/pqxx>

class Connection {
public:
    explicit Connection(const std::string& connectionString);
    ~Connection();
    pqxx::connection* get();

private:
    pqxx::connection* conn;
};
