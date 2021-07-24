#include "Quit.hpp"
#include "Server.h"
Quit::Quit()
{
}

Quit::~Quit()
{
}

Quit::Quit(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "QUIT", arguments)
{
	
}

Quit *Quit::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Quit(full_command, arguments);
}

bool Quit::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	server._to_delete.push(server._users.find(client.get_nickname()));
	for (std::map<std::string, Channel>::iterator it = server._channels.begin() ; it != server._channels.end(); it++)
		(*it).second.users.erase(client.get_nickname());
	std::cout << "Quit works!" << std::endl;
	return true;
}

// std::string Quit::getCommandName() 
// {
// 	return ("QUIT");
// }