#pragma once

#include "OperatorsCommand.hpp"

class Mode: public OperatorsCommand
{
public:
    Mode();
	Mode(std::vector<std::string>  arguments);
    Mode(const Mode &);

    Mode &operator=(const Mode &);
    ~Mode();

	virtual Mode *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    
};

