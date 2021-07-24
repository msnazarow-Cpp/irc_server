#include "Join.hpp"
#include "Server.h"
#include "Parse.hpp"
Join::Join()
{
}

Join::~Join()
{
}

Join::Join(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "JOIN", arguments)
{
	if (arguments.size() > 2)
		throw Parse::ThoManyArgs();
	if (arguments.size() == 0)
		throw WrongArgumentsNumber();
	if (arguments[0][0] != '#')
		throw WrongChannelName();
	_channels = ft::split(arguments[0], ',');
	if (arguments.size() == 2)
		_keys = ft::split(arguments[1], ',');
}

Join *Join::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Join(full_command, arguments);
}

bool Join::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	std::string clientName = client.get_nickname();
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i][0] != '#')
			throw WrongChannelName();
		if(server._channels.count(_channels[i]) == 0)
			{
				server._channels[_channels[i]].users[clientName].first = &client;
				server._users[clientName]->_channels[_channels[i]] = &server._channels[_channels[i]];
				server._channels[_channels[i]].users[clientName].second.insert('w');
				server._channels[_channels[i]].users[clientName].second.insert('r');
				server._channels[_channels[i]].users[clientName].second.insert('o');
			}
		else if (server._channels[_channels[i]].users.count(clientName) == 0)
		{
			server._channels[_channels[i]].users[clientName].first = &client;
			server._channels[_channels[i]].users[clientName].second.insert('w');
			server._channels[_channels[i]].users[clientName].second.insert('r');
		}
		
		for (std::map<std::string, std::pair<Client *, std::set<char> > >::iterator  it = server._channels[_channels[i]].users.begin(); it != server._channels[_channels[i]].users.end(); it++)
		{
			server._users[(*it).first]->_received_msgs.push(notification("JOIN :" + _channels[i] ,client));
		}
		_message = "";
		for (std::map<std::string, std::pair<Client *, std::set<char> > >::iterator  it = server._channels[_channels[i]].users.begin(); it != server._channels[_channels[i]].users.end(); it++)
		{
			_message += (*it).first + " ";
		}
		client._received_msgs.push(clientReply(Message(RPL_NAMREPLY, "= " + _channels[i] + " :@" + _message), client));
		client._received_msgs.push(clientReply(Message(RPL_ENDOFNAMES, _channels[i] + " " RPL_ENDOFNAMES_MESS),client));
		//:irc.server.net 353 Phyre = #SomeChannel :@WiZ
	}
	
	std::cout << "Join works!" << std::endl;
	return false;
}

// std::string Join::getCommandName() 
// {
// 	return ("JOIN");
// }