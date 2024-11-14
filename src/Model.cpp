#include "Model.hpp"
#include <pqxx/pqxx>
#include <iostream>
#include <sstream>
#include <optional>
#include <map>

Model::Model(Connection *dbConn, const std::string &table) : dbConn(dbConn), tableName(table) {}

bool Model::save(const std::map<std::string, std::string> &data)
{
    try
    {
        pqxx::work txn(*dbConn->get());

        std::string fields, values;
        for (const auto &[field, value] : data)
        {
            if (!fields.empty())
            {
                fields += ", ";
                values += ", ";
            }
            fields += field;
            values += txn.quote(value);
        }

        std::string query = "INSERT INTO " + tableName + " (" + fields + ") VALUES (" + values + ") RETURNING id";
        pqxx::result result = txn.exec(query);
        txn.commit();

        if (!result.empty())
        {
            int newId = result[0][0].as<int>();
            std::cout << "Record saved with ID: " << newId << std::endl;
            return true;
        }
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::map<std::string, std::string>> Model::find(int id)
{
    try
    {
        pqxx::work txn(*dbConn->get());

        std::string query = "SELECT * FROM " + tableName + " WHERE id = " + txn.quote(id);
        pqxx::result result = txn.exec(query);
        txn.commit();

        if (!result.empty())
        {
            std::map<std::string, std::string> record;
            for (pqxx::row::size_type i = 0; i < result.columns(); ++i)
            {
                record[result.column_name(i)] = result[0][i].c_str();
            }
            return record;
        }
        else
        {
            return std::nullopt;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool Model::remove(int id)
{
    try
    {
        pqxx::work txn(*dbConn->get());
        std::string query = "DELETE FROM " + tableName + " WHERE id = " + std::to_string(id);
        txn.exec(query);
        txn.commit();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}