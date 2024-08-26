//
// Created by abdennacer on 22/07/24.
//
#include "crudOperations.h"
#include <pqxx/pqxx>
#include <string>
#include "laserpants/dotenv/dotenv.h"
#include <fmt/core.h>
#include "votingSystem.h"

namespace database_operations {
    void database_manager::connect_to_database() {
        database_connection_ = std::make_unique<pqxx::connection>(pqxx::connection(get_url_connection()));
    }

    database_manager::database_manager() {
        connect_to_database();
    }

    void database_manager::execute_query_with_transaction(const std::string& query) const {
        try {
            pqxx::work transaction(*database_connection_);
            (void)transaction.exec(query);
        } catch (const std::exception &e) {
            std::cerr << "Error executing query: " << e.what() << std::endl;
        }
    }
    pqxx::result database_manager::execute_query_without_transaction(const std::string& query) const{
        pqxx::result rows;
        try {
            pqxx::nontransaction non_txn(*database_connection_);
            rows = non_txn.exec(query);
        } catch (const std::exception &e) {
            std::cerr << "Error executing query: " << e.what() << std::endl;
        }
        return rows;
    }

    // Getter for the connection
    pqxx::connection* database_manager::get_connection() const {
        return database_connection_.get();
    }


    std::string get_url_connection() {
        // Load the .env file
        dotenv::init("../.env");
        std::string db_user = dotenv::getenv("DB_USER");
        std::string db_password = dotenv::getenv("DB_PASSWORD");
        std::string db_host = dotenv::getenv("DB_HOST");
        std::string db_port = dotenv::getenv("DB_PORT");
        std::string db_name = dotenv::getenv("DB_NAME");
        std::string connection_url = fmt::format(
            "user={} password={} host={} port={} dbname={} target_session_attrs=read-write",
            db_user, db_password, db_host, db_port, db_name
        );
        return connection_url;
    }
    pqxx::connection connect_database_operations() {
        pqxx::connection connection(get_url_connection());
        return connection;
    }
}

