// demo/main.cpp
#include "Connection.hpp"
#include "SchemaManager.hpp"
#include "Model.hpp"
#include <iostream>

int main()
{
    try
    {
        Connection conn("dbname=ashserver_dev user=postgres password=bdhjiuuedy2yohuf3vuywfeq hostaddr=127.0.0.1 port=5432");
        SchemaManager schemaManager(&conn);
        schemaManager.clearDatabase();
        schemaManager.dropTable("Users");
        std::vector<std::pair<std::string, std::string>> userFields = {
            {"name", "VARCHAR(100)"},
            {"email", "VARCHAR(100)"},
            {"age", "INTEGER"}};

        schemaManager.createTable("users", userFields);
        Model user(&conn, "Users");

        std::map<std::string, std::string> data = {
            {"name", "Nandan Pai"},
            {"email", "nandanrp09@gmail.com"},
            {"age", "20"}};
        std::cout << "Saving a new user..." << std::endl;
        user.save(data);

        std::cout << "Finding user with id 1..." << std::endl;
        auto record = user.find(1);

        if (record)
        {
            for (const auto &[key, value] : *record)
            {
                std::cout << key << ": " << value << std::endl;
            }
        }
        else
        {
            std::cout << "Record not found." << std::endl;
        }
        std::cout << "Deleting user with id 1..." << std::endl;
        user.remove(1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
