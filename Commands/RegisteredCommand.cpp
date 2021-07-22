#include "RegisteredCommand.hpp"
#include "Client.h"

RegisteredCommand::RegisteredCommand()
{
}

RegisteredCommand::RegisteredCommand(const RegisteredCommand &)
{
	
}

RegisteredCommand& RegisteredCommand::operator=(const RegisteredCommand &) 
{
	return (*this);
}

bool RegisteredCommand::execute(Server & server, Client & client) {
	if (client.status() != registered_user)
		throw NotRegistered();
	return false;
}

RegisteredCommand::~RegisteredCommand()
{
}
RegisteredCommand::RegisteredCommand(std::string command_name, std::vector<std::string> arguments)
	: Command(command_name, arguments)
{
	
}
