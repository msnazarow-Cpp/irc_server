#pragma once
#include "RegisteredCommand.hpp"
class OperatorsCommand : public RegisteredCommand
{
public:
	OperatorsCommand();
	OperatorsCommand(const OperatorsCommand &);
	OperatorsCommand(std::string command_name, std::vector<std::string> arguments);
	OperatorsCommand &operator=(const OperatorsCommand &);
	virtual bool execute(Server & server, Client & client);
	~OperatorsCommand();

private:
	
};

