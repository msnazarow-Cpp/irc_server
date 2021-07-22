#include "Join.hpp"
#include "Server.h"
Join::Join()
{
}

Join::~Join()
{
}

Join::Join(std::vector<std::string> arguments): RegisteredCommand("JOIN", arguments)
{
	if (arguments.size() == 0 || arguments.size() > 2)
		throw WrongArgumentsNumber();
	if (arguments[0][0] != '#')
		throw WrongChannelName();
	_channels = ft::split(arguments[0], ',');
	if (arguments.size() == 2)
		_keys = ft::split(arguments[1], ',');
}

Join *Join::create(std::vector<std::string> arguments)
{
	return new Join(arguments);
}

bool Join::execute(Server & server, Client & client)
{
	RegisteredCommand::execute(server, client);
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i][0] != '#')
			throw WrongChannelName();
		if(server._channels.count(_channels[i]) == 0)
			{
				server._channels[_channels[i]].users[client.get_nickname()].insert('w');
				server._channels[_channels[i]].users[client.get_nickname()].insert('r');
				server._channels[_channels[i]].users[client.get_nickname()].insert('o');
			}
		else if (server._channels[_channels[i]].users.count(client.get_nickname()) == 0)
		{
			server._channels[_channels[i]].users[client.get_nickname()].insert('w');
			server._channels[_channels[i]].users[client.get_nickname()].insert('r');
		}
	}
	std::cout << "Join works!" << std::endl;
	return false;
}

// std::string Join::getCommandName() 
// {
// 	return ("JOIN");
// }