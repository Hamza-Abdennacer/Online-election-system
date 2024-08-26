//
// Created by abdennacer on 22/07/24.
//
#ifndef CRUDOPERATIONS_H
#define CRUDOPERATIONS_H

#include <pqxx/pqxx>




namespace database_operations {
    class database_manager {
    public:
        database_manager();
        void execute_query_with_transaction(const std::string& query) const;
        [[nodiscard]] pqxx::result execute_query_without_transaction(const std::string& query) const;
        [[nodiscard]] pqxx::connection* get_connection() const;
    private:
        void connect_to_database();
        std::unique_ptr<pqxx::connection> database_connection_;
    };

    std::string get_url_connection();
    pqxx::connection connect_database_operations();
}

#endif //CRUDOPERATIONS_H
