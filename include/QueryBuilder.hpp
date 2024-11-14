#pragma once
#include <string>

class QueryBuilder {
public:
    QueryBuilder& select(const std::string& fields);
    QueryBuilder& from(const std::string& table);
    QueryBuilder& where(const std::string& condition);
    std::string build();

private:
    std::string query;
};
