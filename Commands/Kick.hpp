#pragma once

#include "OperatorsCommand.hpp"

class Kick: public OperatorsCommand
{
public:
    Kick();
	Kick(const std::string & full_command, const std::vector<std::string> & arguments);
    Kick(const Kick &);

    Kick &operator=(const Kick &);
    ~Kick();

	virtual Kick *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    
};

