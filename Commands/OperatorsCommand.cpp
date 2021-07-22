#include "OperatorsCommand.hpp"
OperatorsCommand::OperatorsCommand(const OperatorsCommand &) 
{
	
}

OperatorsCommand::OperatorsCommand(std::string command_name, std::vector<std::string> arguments)
	: RegisteredCommand(command_name, arguments)
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
