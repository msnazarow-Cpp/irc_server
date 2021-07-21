#pragma once

#include "Command.hpp"

class Part : public Command
{
public:
    Part();
	Part(std::vector<std::string>  arguments);
    Part(const Part &);

    Part &operator=(const Part &);
    ~Part();

	virtual Part *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();
private:
    
};

