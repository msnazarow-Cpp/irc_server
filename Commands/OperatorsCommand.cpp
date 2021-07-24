#include "OperatorsCommand.hpp"
OperatorsCommand::OperatorsCommand(const OperatorsCommand &) 
{
	
}

OperatorsCommand::OperatorsCommand(const std::string & full_command, const std::string & command_name, const std::vector<std::string> & arguments)
	: RegisteredCommand(full_command, command_name, arguments)
{
	
}

OperatorsCommand &OperatorsCommand::operator=(const OperatorsCommand &) {
	return (*this);
}

bool OperatorsCommand::execute(Server & server, Client & client) 
{
	return false;
}

OperatorsCommand::~OperatorsCommand()
{
	
}

OperatorsCommand::OperatorsCommand() 
{
	
}
