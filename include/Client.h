#pragma once

#include "ServConfig.h"
#include "Request.h"
#include "Message.h"
#include <sys/time.h>
#include <cmath>
#include <queue>

class Client {
public:
    Client(int fd);
    ~Client();

private:
    const int fd_;
    e_client_status next_status;
    size_t _sended;
    std::string _raw_msg;
    enum e_client_status _status;
    Request _req;

   //NEW
    std::queue<Message> _received_msgs;
    //std::queue<Command> _received_commands;
    std::string _nick;
public:
    bool receive();

    bool response();

    void raw_send();

    e_client_status GetStatus();

    int getFd() const;
};
