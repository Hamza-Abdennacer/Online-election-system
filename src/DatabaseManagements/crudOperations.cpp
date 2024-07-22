//
// Created by abdennacer on 22/07/24.
//
#include "crudOperations.h"
#include <iostream>
#include <pqxx/pqxx>

namespace database_operations {
    // Helper function to join columns or clauses
    std::string join(const std::vector<std::string> &elements, const std::string &delimiter) {
        std::string result;
        for (size_t i = 0; i < elements.size(); ++i) {
            if (i > 0) result += delimiter;
            result += elements[i];
        }
        return result;
    }

    // Helper function to join values
    template <typename... Args>
    std::string joinValues(const std::tuple<Args...> &values) {
        std::string result;
        std::apply([&result](const auto &... args) {
            std::string delimiter;
            ((result += delimiter + pqxx::work::quote(args), delimiter = ", "), ...);
        }, values);
        return result;
    }

    void createRecord(pqxx::connection &c, const std::string &table, const std::vector<std::string> &columns, const std::tuple<int, std::string, std::string> &values) {
        try {
            pqxx::work txn(c);
            std::string columns_str = join(columns, ", ");
            std::string values_str = joinValues(values);
            std::string sql = "INSERT INTO " + table + " (" + columns_str + ") VALUES (" + values_str + ");";
            txn.exec(sql);
            txn.commit();
            std::cout << "Record inserted successfully into " << table << "." << std::endl;
        }
        catch (const pqxx::sql_error &e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void readRecords(pqxx::connection &c, const std::string &table) {
        try {
            pqxx::nontransaction txn(c);
            std::string sql = "SELECT * FROM " + table + ";";
            pqxx::result res = txn.exec(sql);
            for (auto row : res) {
                for (auto field : row) {
                    std::cout << field.c_str() << " ";
                }
                std::cout << std::endl;
            }
        }
        catch (const pqxx::sql_error &e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void updateRecord(pqxx::connection &c, const std::string &table, const std::vector<std::string> &set_clauses, const std::string &condition) {
        try {
            pqxx::work txn(c);
            std::string set_clause_str = join(set_clauses, ", ");
            std::string sql = "UPDATE " + table + " SET " + set_clause_str + " WHERE " + condition + ";";
            txn.exec(sql);
            txn.commit();
            std::cout << "Record updated successfully in " << table << "." << std::endl;
        }
        catch (const pqxx::sql_error &e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void deleteRecord(pqxx::connection &c, const std::string &table, const std::string &condition) {
        try {
            pqxx::work txn(c);
            std::string sql = "DELETE FROM " + table + " WHERE " + condition + ";";
            txn.exec(sql);
            txn.commit();
            std::cout << "Record deleted successfully from " << table << "." << std::endl;
        }
        catch (const pqxx::sql_error &e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
            std::cerr << "Query was: " << e.query() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}