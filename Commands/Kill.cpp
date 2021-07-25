#include "Kill.hpp"
#include "Quit.hpp"
#include <set>
#include "Client.h"
#include "Channel.h"
#include "Server.h"

Kill::Kill()
{
}

Kill::~Kill()
{
}

Kill::Kill(const std::string & full_command, const std::vector<std::string> & arguments): OperatorsCommand(full_command, "KILL", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kill *Kill::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Kill(full_command, arguments);
}

bool Kill::execute(Server & server, Client & client)
{
	if (!client._priveleges.count('O'))
		{
			client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOPRIVILEGES,ERR_NOPRIVILEGES_MESS),client));
			return false;
		}
	if (OperatorsCommand::execute(server, client))
		return(true);
	std::set<SharedPtr<Client> > releted_users;
	releted_users.insert(server._users[client.get_nickname()]);
	for (std::map<std::string, Channel *>::iterator it_ch = client._channels.begin(); it_ch != client._channels.end(); it_ch++)
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = server._channels[(*it_ch).first].users.begin(); it != server._channels[(*it_ch).first].users.end(); it++)
			releted_users.insert(server._users[(*it).first]);
	server._users[_arguments[0]]->_received_msgs.push("ERROR :KILLed by " + client.get_nickname() + ": " +_arguments[1] + "\r\n");
	server._to_delete.push_back(server._users.find(_arguments[0]));
	_full_command = "QUIT :KILLed by " + client.get_nickname() + ": " +_arguments[1];
	
	for (std::set<SharedPtr<Client> >::iterator it = releted_users.begin(); it != releted_users.end(); it++)
		(*it)->_received_msgs.push(notification(*server._users[_arguments[0]], this));
	for (std::map<std::string, Channel>::iterator it = server._channels.begin(); it != server._channels.end(); it++)
		(*it).second.users.erase(_arguments[0]);
	std::cout << "Kill works!" << std::endl;
	return true;
}

// std::string Kill::getCommandName() 
// {
// 	return ("KILL");
// }