#pragma once

#include "RegisteredCommand.hpp"

class Part : public RegisteredCommand
{
public:
    Part();
	Part(std::vector<std::string>  arguments);
    Part(const Part &);

    Part &operator=(const Part &);
    ~Part();

	virtual Part *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    
};

