cmake_minimum_required(VERSION 3.17)
project(webserv)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-Wall -Werror -g -MMD -D_GLIBCXX_DEBUG -fsanitize=address")
include_directories(include
        Commands
        .)

add_executable(bot bot/main.cpp src/utils.cpp)

add_executable(test_server
        src/Server.cpp
        src/utils.cpp
        src/main.cpp
        src/Client.cpp
        src/Channel.cpp
        src/Message.cpp
        Commands/Parse.cpp
        Commands/Who.cpp
        Commands/Notice.cpp
        Commands/List.cpp
        Commands/Command.cpp
        Commands/Invite.cpp
        Commands/Join.cpp
        Commands/Kick.cpp
        Commands/Kill.cpp
        Commands/Mode.cpp
        Commands/Nick.cpp
        Commands/Oper.cpp
        Commands/OperatorsCommand.cpp
        Commands/Part.cpp
        Commands/Pass.cpp
        Commands/Privmsg.cpp
        Commands/Quit.cpp
        Commands/RegisteredCommand.cpp
        Commands/User.cpp
        )
