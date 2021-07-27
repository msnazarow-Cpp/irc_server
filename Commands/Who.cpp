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
			_recipients_types[0] = channel;
		else
			_recipients_types[0] = user;
		_recipients[0] = arguments[0];
	}
	else
	{
		_recipients_types[0] = channel;
		_recipients[0] = "*";
	}
}

Who *Who::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Who(full_command, arguments);
}

//remove ~
std::string Who::response(std::string channelName, Server & server, Client & client)
{
	return (channelName + " " + client.get_username() + " " + client.get_hostname() + " " + server.hostIp() + " " + 
	client.get_nickname() + " H" + (channelName != "*" && client._channels[channelName]->users[client.get_nickname()].second.count('o') ? "@" : "") 
	+ (client._priveleges.count('O') ? "*" : "") + " :0 " + client.get_realname());
}
std::string Who::response(Server & server, Client & client)
{
	return ("* " + client.get_username() + " " + client.get_hostname() + " " + server.hostIp() + " " + client.get_nickname() + " H :0 " + client.get_realname());
}
bool Who::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	if (_recipients_types[0] == channel)
	{
		if (_recipients[0] == "*")
			for (Server::Clients_map::iterator it = server._users.begin(); it != server._users.end() ; it++)
			{
				client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOREPLY, response(server, *(*it).second)),client));
			}
		else
		{
			for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = server._channels[_recipients[0]].users.begin(); it != server._channels[_recipients[0]].users.end() ; it++)
			{
				client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOREPLY, response(_recipients[0], server, *(*it).second.first)),client));
			}
		}
	}
	else if (server._users.count(_recipients[0]) != 0)
	{
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOREPLY, response("*", server, server._users[_])),client));
        client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_ENDOFWHO, RPL_ENDOFWHO_MESS),client));
	}
	else
        client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHNICK,ERR_NOSUCHNICK_MESS),client));

    std::cout << "Who works!" << std::endl;
	return true;
}

// std::string Who::getCommandName() 
// {
// 	return ("Who");
// }