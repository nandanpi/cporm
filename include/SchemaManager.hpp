#pragma once
#include "Connection.hpp"
#include <string>
#include <vector>
#include <utility>

class SchemaManager
{
public:
    explicit SchemaManager(Connection *dbConn);
    void createTable(const std::string &tableName, const std::vector<std::pair<std::string, std::string>> &fields);
    void dropTable(const std::string &tableName);
    void clearDatabase();

private:
    Connection *dbConn;
};