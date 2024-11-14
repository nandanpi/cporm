#include "SchemaManager.hpp"
#include <pqxx/pqxx>
#include <iostream>
#include <sstream>

SchemaManager::SchemaManager(Connection *dbConn) : dbConn(dbConn) {}

void SchemaManager::createTable(const std::string &tableName, const std::vector<std::pair<std::string, std::string>> &fields)
{
    pqxx::work txn(*dbConn->get());

    std::stringstream query;
    query << "CREATE TABLE IF NOT EXISTS " << tableName << " (id SERIAL PRIMARY KEY";
    for (const auto &field : fields)
    {
        query << ", " << field.first << " " << field.second;
    }
    query << ")";

    txn.exec(query.str());
    txn.commit();
}

void SchemaManager::dropTable(const std::string &tableName)
{
    pqxx::work txn(*dbConn->get());
    std::string query = "DROP TABLE IF EXISTS " + tableName;
    txn.exec(query);
    txn.commit();
}

void SchemaManager::clearDatabase()
{
    try
    {
        pqxx::work txn(*dbConn->get());
        pqxx::result tables = txn.exec("SELECT tablename FROM pg_tables WHERE schemaname='public'");

        for (const auto &row : tables)
        {
            std::string tableName = row["tablename"].c_str();
            std::string dropQuery = "DROP TABLE IF EXISTS \"" + tableName + "\" CASCADE";
            txn.exec(dropQuery);
        }

        txn.commit();
        std::cout << "All tables dropped successfully. Database is now clear." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error clearing database: " << e.what() << std::endl;
    }
}