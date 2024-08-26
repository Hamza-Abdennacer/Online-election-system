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

# Include FetchContent module
include(FetchContent)

# Fetch libpqxx
FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG        7.6.0
)

# Make libpqxx available
FetchContent_MakeAvailable(libpqxx)

# Add the executable
add_executable(OnlineVotingSystem ${SOURCES}
        include/crudOperations.h
        src/DatabaseManagements/crudOperations.cpp
        include/entities/User.cpp
        include/entities/User.h)

# Find PostgreSQL package
find_package(PostgreSQL REQUIRED)

# Find the fmt package
find_package(fmt REQUIRED)

# Link libraries
target_link_libraries(OnlineVotingSystem PRIVATE pqxx pq ${PostgreSQL_LIBRARIES} fmt::fmt)

# Ensure the PostgreSQL include directory is found
include_directories(${PostgreSQL_INCLUDE_DIRS})

# Installation
install(TARGETS OnlineVotingSystem DESTINATION bin)

# Add custom commands or targets if needed (e.g., for database migrations or setup)
