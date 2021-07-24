#pragma once

#include "RegisteredCommand.hpp"
#include "Channel.h"

class Whois : public RegisteredCommand
{
public:
    Whois();
	Whois(const std::string & full_command, const std::vector<std::string> & arguments);
    Whois(const Whois &);
	Whois &operator=(const Whois &);
    ~Whois();

	virtual Whois *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	static std::string response(Server & server, Client & client);
    // virtual const std::string &getCommandName();
private:
    std::string _message;
};

