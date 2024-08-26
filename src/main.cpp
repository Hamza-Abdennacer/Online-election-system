#include <pqxx/pqxx>
#include "laserpants/dotenv/dotenv.h"

#include "crudOperations.h"
#include "votingSystem.h"

int main() {
    displayWelcomeMessage();
    try {
        const database_operations::database_manager database_manager;
        database_manager.execute_query_without_transaction("SELECT * FROM vote");
        std::cout << "Connected to database successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
