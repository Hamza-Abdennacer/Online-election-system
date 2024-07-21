cmake_minimum_required(VERSION 3.10)

# Project name
project(OnlineVotingSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(MySQL REQUIRED)
# Uncomment below if you're using PostgreSQL or SQLite instead of MySQL
# find_package(PostgreSQL REQUIRED)
# find_package(SQLite3 REQUIRED)

# Add the executable
add_executable(OnlineVotingSystem ${SOURCES})

# Link libraries
target_link_libraries(OnlineVotingSystem OpenSSL::SSL OpenSSL::Crypto Boost::system Boost::filesystem ${MYSQL_LIBRARIES})
# Uncomment below if you're using PostgreSQL or SQLite instead of MySQL
# target_link_libraries(OnlineVotingSystem PostgreSQL::PostgreSQL)
# target_link_libraries(OnlineVotingSystem SQLite::SQLite3)

# Installation
install(TARGETS OnlineVotingSystem DESTINATION bin)

# Add custom commands or targets if needed (e.g., for database migrations or setup)
