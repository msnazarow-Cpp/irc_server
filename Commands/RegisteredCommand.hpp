#pragma once

#include "Command.hpp"

class RegisteredCommand : public Command
{
public:
	RegisteredCommand();
	RegisteredCommand(const RegisteredCommand &);
	RegisteredCommand &operator=(const RegisteredCommand &);
	RegisteredCommand(std::string command_name, std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	~RegisteredCommand();

private:
	
};
