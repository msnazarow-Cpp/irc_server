#pragma once

#include "OperatorsCommand.hpp"

class Kick: public OperatorsCommand
{
public:
    Kick();
	Kick(std::vector<std::string>  arguments);
    Kick(const Kick &);

    Kick &operator=(const Kick &);
    ~Kick();

	virtual Kick *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    
};

