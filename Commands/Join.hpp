#pragma once

#include "RegisteredCommand.hpp"
#include <set>
class Join: public RegisteredCommand
{
public:
    Join();
	Join(const std::string & full_command, const std::vector<std::string> & arguments);
    Join(const Join &);

    Join &operator=(const Join &);
    ~Join();

	virtual Join *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::vector<std::string> _channels;
	std::vector<std::string> _keys;
};

