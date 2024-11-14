#pragma once
#include "Connection.hpp"
#include <string>
#include <map>
#include <optional>

class Model
{
public:
    explicit Model(Connection *dbConn, const std::string &table);
    bool save(const std::map<std::string, std::string> &data);
    std::optional<std::map<std::string, std::string>> find(int id);
    bool remove(int id);

protected:
    Connection *dbConn;
    std::string tableName;
};