#include "Kick.hpp"
#include "Server.h"

Kick::Kick()
{
}

Kick::~Kick()
{
}

Kick::Kick(const std::string & full_command, const std::vector<std::string> & arguments): OperatorsCommand(full_command, "KICK", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kick *Kick::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Kick(full_command, arguments);
}

bool Kick::execute(Server & server, Client & client)
{
	OperatorsCommand::execute(server, client);

	std::string & channel_name = _arguments[0];
	std::string & nick_name = _arguments[1];
	if (server._channels.count(channel_name))
	{
		if (server._channels[channel_name].users[client.get_nickname()].second.count('o'))
		{
			if (server._channels[channel_name].users.count(nick_name))
			{
				for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator 
						it = server._channels[channel_name].users.begin();
						it != server._channels[channel_name].users.end(); it++)
					(*it).second.first->_received_msgs.push(notification(client, this));
				server._channels[channel_name].users.erase(nick_name);
			}
			else
				client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MESS),client));
		}
		else
			client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MESS),client));
	}
	else
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MESS),client));
	std::cout << "Kick works!" << std::endl;
	return false;
}

// std::string Kick::getCommandName() 
// {
// 	return ("KICK");
// }