#pragma once

#include "Command.hpp"

class Kill: public Command
{
public:
    Kill();
	Kill(std::vector<std::string> arguments);
    Kill(const Kill &);

    Kill &operator=(const Kill &);
    ~Kill();

	virtual Kill *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();
private:
    
};

