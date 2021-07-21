#pragma once

#include "ServConfig.h"
#include "Message.h"
#include <sys/time.h>
#include <cmath>
#include <queue>
#include "SharedPtr.h"
#include "Message.h"

class Server;
class Client;

class Command{
public:
    Command(const std::string& basicString, const std::string&);
    std::string msg;
    std::string dst;
    std::string client_nick;
    void exec(Server*);
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
private:
    std::string _nick;
public:
    void setNick(const std::string &nick);

public:
    const std::string &getNick() const;

private:
    std::string _raw_data;
    std::string _raw_send;
public:

    bool receive(bool);
    bool response();
    void raw_send();
    //e_client_status GetStatus();
    int getFd() const;
    void Combine_messages();
    void addMsg(const Message &msg);

    Command getCommand();
    bool hasCommands() const;
};
