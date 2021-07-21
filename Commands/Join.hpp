#pragma once

#include "Command.hpp"

class Join: public Command
{
public:
    Join();
	Join(std::vector<std::string>  arguments);
    Join(const Join &);

    Join &operator=(const Join &);
    ~Join();

	virtual Join *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();
private:
    
};

