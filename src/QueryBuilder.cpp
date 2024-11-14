#include "QueryBuilder.hpp"

QueryBuilder& QueryBuilder::select(const std::string& fields) {
    query += "SELECT " + fields;
    return *this;
}

QueryBuilder& QueryBuilder::from(const std::string& table) {
    query += " FROM " + table;
    return *this;
}

QueryBuilder& QueryBuilder::where(const std::string& condition) {
    query += " WHERE " + condition;
    return *this;
}

std::string QueryBuilder::build() {
    return query;
}
