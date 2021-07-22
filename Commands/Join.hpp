#pragma once

#include "RegisteredCommand.hpp"
#include <set>
class Join: public RegisteredCommand
{
public:
    Join();
	Join(std::vector<std::string>  arguments);
    Join(const Join &);

    Join &operator=(const Join &);
    ~Join();

	virtual Join *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    std::vector<std::string> _channels;
	std::vector<std::string> _keys;
};

