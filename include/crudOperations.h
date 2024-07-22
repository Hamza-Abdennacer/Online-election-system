//
// Created by abdennacer on 22/07/24.
//

#ifndef CRUDOPERATIONS_H
#define CRUDOPERATIONS_H

#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <tuple>


namespace database_operations {
    void create_record(pqxx::connection &c, const std::string &table, const std::vector<std::string> &columns, const std::tuple<int, std::string, std::string> &values);
    void read_records(pqxx::connection &c, const std::string &table);
    void update_record(pqxx::connection &c, const std::string &table, const std::vector<std::string> &set_clauses, const std::string &condition);
    void delete_record(pqxx::connection &c, const std::string &table, const std::string &condition);
}

#endif //CRUDOPERATIONS_H
