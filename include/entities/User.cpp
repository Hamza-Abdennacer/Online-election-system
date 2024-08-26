//
// Created by abdennacer on 19/08/24.
//

#include "User.h"
#include "crudOperations.h"
#include <utility>
#include <pqxx/pqxx>

namespace entities {
    user::user(std::string username, std::string password, std::string email) {
        username_ = std::move(username);
        password_ = std::move(password);
        email_ = std::move(email);
    }

    std::string user::get_email() {
        return email_;
    }
    std::string user::get_username() {
        return username_;
    }

    void user::set_email(std::string email) {
        email_ = std::move(email);
    }

    void user::set_password(std::string password) {
        password_ = std::move(password);
    }

    void user::set_username(std::string name) {
        username_ = std::move(name);
    }

    // database operations
    user user::create_user(const database_operations::database_manager &database_manager, std::string email, std::string password, std::string username) {
        const std::string request = "INSERT INTO user (username, email, password) VALUES (" + email + ", " + password + ", " + username + ")";
        database_manager.execute_query_with_transaction(request);
        return {std::move(username), std::move(password), std::move(email)};
    }

    user user::get_user(const database_operations::database_manager &database_manager, const std::string& email) {
        const std::string query = "SELECT * FROM user WHERE email = '" + email + "'";
        const pqxx::result rows = database_manager.execute_query_without_transaction(query);
        user user*;
        for (auto && row : rows) {
            auto [id, username, email, password] = row.as<int, std::string, std::string, std::string>();
            user = user(std::move(username), std::move(password), std::move(email));
            break;
        }
        return *user;
    }

    user user::connect_user(const database_operations::database_manager &database_manager, std::string password, std::string email) {
        const std::string query = "SELECT * FROM user WHERE email = '" + email + "'";
        const pqxx::result rows = database_manager.execute_query_without_transaction(query);
        user user*;
        if (rows.empty()) {
            throw std::runtime_error("No user found");
        }
        for (auto && row : rows) {
            auto [id, username, email, password] = row.as<int, std::string, std::string, std::string>();
            user = user(std::move(username), std::move(password), std::move(email));
            break;
        }
        if (password != user->get_password()) {
            throw std::runtime_error("Password does not match the password");
        }
        return *user;
    }







}