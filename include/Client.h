#pragma once

#include "ServConfig.h"
#include "Request.h"
#include "Message.h"
#include <sys/time.h>
#include <cmath>
#include <queue>

class Command{
public:
    Command(std::basic_string<char> basicString);
};//TODO sgertrud

class Client {
public:
    Client(int fd);
    ~Client();

private:
    const int _fd;

   //NEW
    std::queue<Message> _received_msgs;
    std::queue<Command> _received_commands;
public:
    const std::queue<Command> &getReceivedCommands() const;

private:
    //std::string _nick;
    std::string _raw_data;
public:
    bool receive(bool);

    bool response();

    void raw_send();

    e_client_status GetStatus();

    int getFd() const;
};
