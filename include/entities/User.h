//
// Created by abdennacer on 19/08/24.
//

#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "crudOperations.h"

namespace entities {
    class user {
    public:
        user(std::string username, std::string password, std::string email);
        std::string get_username();
        std::string get_email();
        std::string get_password();
        void set_username(std::string name);
        void set_email(std::string email);
        void set_password(std::string password);
        static user create_user(const database_operations::database_manager &database_manager, std::string email, std::string password, std::string username);
        void delete_user(user user);
        void modify_user(user user);
        static user get_user(const database_operations::database_manager &database_manager, const std::string& email);
        std::vector<user> get_all_users();

        static user connect_user(const database_operations::database_manager &database_manager, std::string password, std::string email);
    private:
        int id_;
        std::string username_;
        std::string email_;
        std::string password_;
    };
}



#endif //USER_H
