cmake_minimum_required(VERSION 3.17)
project(webserv)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
include_directories(
        include
        Commands
        )

add_executable(test_server
        src/Server.cpp
        src/utils.cpp
        src/main.cpp
        src/Client.cpp
        src/response.cpp
#        src/Channel.cpp
)
