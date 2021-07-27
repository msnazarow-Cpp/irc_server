#pragma once

#include "RegisteredCommand.hpp"
#include <set>
#include "Channel.h"

class Topic: public RegisteredCommand
{
public:
    Topic();
	Topic(const std::string & full_command, const std::vector<std::string> & arguments);
    Topic(const Topic &);

    Topic &operator=(const Topic &);
    ~Topic();
	bool checkBan(std::vector<Channel::BanMask> & ban_list, const std::string & hostIp, Client & client);
	virtual Topic *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);

private:
    std::string _channel;
	std::vector<std::string> _keys;
};

