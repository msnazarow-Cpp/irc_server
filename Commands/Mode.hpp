#pragma once

#include "OperatorsCommand.hpp"

class Mode: public OperatorsCommand
{
public:
    Mode();
	Mode(const std::string & full_command, const std::vector<std::string> & arguments);
    Mode(const Mode &);

    Mode &operator=(const Mode &);
    ~Mode();

	virtual Mode *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    
};

