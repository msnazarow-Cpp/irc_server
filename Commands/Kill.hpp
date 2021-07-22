#pragma once

#include "OperatorsCommand.hpp"

class Kill: public OperatorsCommand
{
public:
    Kill();
	Kill(std::vector<std::string> arguments);
    Kill(const Kill &);

    Kill &operator=(const Kill &);
    ~Kill();

	virtual Kill *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    
};

