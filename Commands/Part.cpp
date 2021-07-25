#include "Part.hpp"
#include "Server.h"
Part::Part()
{
}

Part::~Part()
{
}

Part::Part(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "PART", arguments)
{
	if (arguments.size() < 1)
		throw WrongArgumentsNumber();
	_channels = ft::split(arguments[0], ',');
	if (arguments.size() == 2)
	{
		_message = arguments[1];
	}
}

Part *Part::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	
	return new Part(full_command, arguments);
}

bool Part::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i][0] != '#')
			throw WrongChannelName();
		if(server._channels.count(_channels[i]) == 0)
			throw WrongChannelName();
		else if (server._channels[_channels[i]].users.count(client.get_nickname()) == 0)
			throw WrongChannelName();
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = server._channels[_channels[i]].users.begin(); it != server._channels[_channels[i]].users.end(); it++)
		{
			server._users[(*it).first]->_received_msgs.push(notification("PART " + _channels[i] + " :" + _message ,client));
		}
		server._channels[_channels[i]].users.erase(client.get_nickname());
	}
	
	std::cout << "Part works!" << std::endl;
	return false;
}

// std::string Part::getCommandName() 
// {
// 	return ("PART");
// }