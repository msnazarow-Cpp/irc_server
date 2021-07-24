#pragma once

#include "OperatorsCommand.hpp"

class Kill: public OperatorsCommand
{
public:
    Kill();
	Kill(const std::string & full_command, const std::vector<std::string> & arguments);
    Kill(const Kill &);

    Kill &operator=(const Kill &);
    ~Kill();

	virtual Kill *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    
};

