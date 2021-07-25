#include "RegisteredCommand.hpp"
#include "Client.h"
#include "Server.h"
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
	client.touch_check = true;
	if (!client.reg_check)
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOTREGISTERED, ":"),client));
	return !client.reg_check;
}

RegisteredCommand::~RegisteredCommand()
{
}
RegisteredCommand::RegisteredCommand(const std::string & full_command, const std::string & command_name, const std::vector<std::string> & arguments)
	: Command(full_command, command_name, arguments)
{
	
}
