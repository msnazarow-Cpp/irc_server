#include "Notice.hpp"
#include "Client.h"
#include "Server.h"
#include <algorithm>
#include "Parse.hpp"

Notice::Notice()
{
}

Notice::~Notice()
{
}

Notice::Notice(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "Notice", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
	if (arguments.size() > 3)
		throw Parse::ThoManyArgs();
	_recipients = ft::split(arguments[0], ',');
	for (size_t i = 0; i < _recipients.size(); i++)
		if (_recipients[i][0] == '#')
			_recipients_types[i] = channel;
		else
			_recipients_types[i] = user;
	_message = arguments[1];
}

Notice *Notice::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Notice(full_command, arguments);
}

bool Notice::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	for (size_t i = 0; i < _recipients.size(); i++)	
	{	
		if (_recipients_types[i] == user)
		{
			if (server._users.count(_recipients[i]) == 0)
				continue ;
			else
				server._users[_recipients[i]]->_received_msgs.push(notification("NOTICE " + _recipients[i]	+ " :" + _message, client));
		}
		else
		{
			if(server._channels.count(_recipients[i]) == 0)
				continue ;
			std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > > & users = server._channels[_recipients[i]].users;
			if (users.count(client.get_nickname()) == 0)
				continue ;
			else if (users[client.get_nickname()].second.count('w') == 0)
				continue ;
			else
			{
				for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = users.begin(); it != users.end(); it++)
					if ((*it).second.second.count('r') && (*it).first != client.get_nickname())
						server._users[(*it).first]->_received_msgs.push(notification("NOTICE " + _recipients[i] + " :" + _message, client));
			}
		}
	}
	
	std::cout << "Notice works!" << std::endl;
	return false;
}