#include "Connection.hpp"
#include <stdexcept>

Connection::Connection(const std::string& connectionString) {
    conn = new pqxx::connection(connectionString);
    if (!conn->is_open()) {
        throw std::runtime_error("Cannot open database connection");
    }
}

Connection::~Connection() {
    conn->close();
    delete conn;
}

pqxx::connection* Connection::get() {
    return conn;
}
