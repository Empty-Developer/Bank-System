cmake_minimum_required(VERSION 3.10)
project(BankSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add pthread for threading support
find_package(Threads REQUIRED)

# Executable
add_executable(bank_sim
    src/main.cpp
    src/Account.cpp
    src/Bank.cpp
    src/Client.cpp
    src/Logger.cpp
    src/Transaction.cpp
)

target_include_directories(bank_sim PRIVATE src)
target_link_libraries(bank_sim Threads::Threads)

# Compiler flags for debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -O0")