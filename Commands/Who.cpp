#include "Who.hpp"
#include "Client.h"
#include "Server.h"
#include "Parse.hpp"
Who::Who()
{
}

Who::~Who()
{
}

Who::Who(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "Who", arguments)
{
	if (arguments.size() > 2)
		throw Parse::ThoManyArgs();
	else if (arguments.size() != 0)
	{
		if(arguments[0][0] == '#')
			_recipient_type = channel;
		else
			_recipient_type = user;
		_recipient = arguments[0];
	}
	else
	{
		_recipient_type = channel;
		_recipient = "*";
	}
}

Who *Who::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Who(full_command, arguments);
}

std::string Who::response(std::string channelName, Server & server, Client & client)
{
	return (channelName + " " + "~" + client.get_username() + " " + client.get_hostname() + " " + server.hostIp() + " " + client.get_nickname() + " H :0 " + client.get_realname());
}
std::string Who::response(Server & server, Client & client)
{
	return ("* ~" + client.get_username() + " " + client.get_hostname() + " " + server.hostIp() + " " + client.get_nickname() + " H :0 " + client.get_realname());
}
bool Who::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	if (_recipient_type == channel)
	{
		if (_recipient == "*")
			for (Server::Clients_map::iterator it = server._users.begin(); it != server._users.end() ; it++)
			{
				client._received_msgs.push(clientReply(Message(RPL_WHOREPLY, response(server, *(*it).second)),client));
			}
		else
		{
			for (std::map<std::string, std::pair<Client *, std::set<char> > >::iterator it = server._channels[_recipient].users.begin(); it != server._channels[_recipient].users.end() ; it++)
			{
				client._received_msgs.push(clientReply(Message(RPL_WHOREPLY, response(_recipient, server, *(*it).second.first)),client));
			}
		}
	}
	else
		client._received_msgs.push(clientReply(Message(RPL_WHOREPLY, response("*", server, client)),client));
	// client._received_msgs.push(clientReply(Message(RPL_WHOREPLY, RPL_WHOSTART_MESS),client));
	

	// for (std::map<std::string, Channel>::iterator it = server._channels.begin(); it != server._channels.end(); it++)
	// 	for (std::map<std::string, std::pair<Client *, std::set<char> > >::iterator it_u = (*it).second.users.begin(); it_u != (*it).second.users.end(); it_u++)
	// 		client._received_msgs.push(clientReply(Message(RPL_WHOREPLY, response(it, server, *(*it_u).second.first)),client));
	client._received_msgs.push(clientReply(Message(RPL_ENDOFWHO, RPL_ENDOFWHO_MESS),client));
	std::cout << "Who works!" << std::endl;
	return true;
}

// std::string Who::getCommandName() 
// {
// 	return ("Who");
// }