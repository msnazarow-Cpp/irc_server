#pragma once

#include "RegisteredCommand.hpp"
#include <set>
#include "Channel.h"

class Names: public RegisteredCommand
{
public:
    Names();
	Names(const std::string & full_command, const std::vector<std::string> & arguments);
    Names(const Names &);

    Names &operator=(const Names &);
    ~Names();
	bool checkBan(std::vector<Channel::BanMask> & ban_list, const std::string & hostIp, Client & client);
	virtual Names *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::vector<std::string> _channels;
	std::vector<std::string> _keys;
};

