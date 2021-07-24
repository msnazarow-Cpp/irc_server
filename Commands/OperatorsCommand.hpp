#pragma once
#include "RegisteredCommand.hpp"
class OperatorsCommand : public RegisteredCommand
{
public:
	OperatorsCommand();
	OperatorsCommand(const OperatorsCommand &);
	OperatorsCommand(const std::string & full_command, const std::string & command_name, const std::vector<std::string> & arguments);
	OperatorsCommand &operator=(const OperatorsCommand &);
	virtual bool execute(Server & server, Client & client);
	~OperatorsCommand();

private:
	
};

