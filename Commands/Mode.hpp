#pragma once

#include "Command.hpp"

class Mode: public Command
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

