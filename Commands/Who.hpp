#pragma once

#include "RegisteredCommand.hpp"
#include "Channel.h"

class Who : public RegisteredCommand
{
public:
    Who();
	Who(const std::string & full_command, const std::vector<std::string> & arguments);
    Who(const Who &);
	Who &operator=(const Who &);
    ~Who();

	virtual Who *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	static std::string response(std::string channelName, Server & server, Client & client);
	static std::string response(Server & server, Client & client);

private:

};

