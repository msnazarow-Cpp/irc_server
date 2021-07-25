#pragma once

#include "RegisteredCommand.hpp"
#include <set>
#include "Channel.h"

class Join: public RegisteredCommand
{
public:
    Join();
	Join(const std::string & full_command, const std::vector<std::string> & arguments);
    Join(const Join &);

    Join &operator=(const Join &);
    ~Join();
	bool checkBan(std::vector<Channel::BanMask> & ban_list, const std::string & hostIp, Client & client);
	virtual Join *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::vector<std::string> _channels;
	std::vector<std::string> _keys;
};

