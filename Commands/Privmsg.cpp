#include "Privmsg.hpp"
#include "Client.h"
#include "Server.h"
#include <algorithm>

Privmsg::Privmsg()
{
}

Privmsg::~Privmsg()
{
}

Privmsg::Privmsg(std::vector<std::string> arguments): RegisteredCommand("PRIVMSG", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
	if (arguments[0][0] == '#')
		_recipient_type = channel;
	else
		_recipient_type = user;
	_recipient = arguments[0];
	size_t i = 1;
	while (i < arguments.size())
		_message += arguments[i++];
}

Privmsg *Privmsg::create(std::vector<std::string> arguments)
{
	return new Privmsg(arguments);
}

bool Privmsg::execute(Server & server, Client & client)
{
	RegisteredCommand::execute(server, client);
	if (_recipient_type == user)
	{
		if (server._users.count(_recipient) == 0)
			throw NosuchUser();
		else
			server._users[_recipient]->_received_msgs.push(_message + "\r\n");
	}
	else
	{
		if(server._channels.count(_recipient) == 0)
			throw NosuchChannel();
		std::map<std::string, std::set<char> > & users = server._channels[_recipient].users;
		if (users.count(client.get_nickname()) == 0)
			throw NotJoinYet();
		else if (users[client.get_nickname()].count('w') == 0)
			throw NotHaveWriteRight();
		else
		{
			for (std::map<std::string, std::set<char> >::iterator it = users.begin(); it != users.end(); it++)
				if ((*it).second.count('r'))
					server._users[(*it).first]->_received_msgs.push(_message + "\r\n");
		}
	}
	
	std::cout << "Privmsg works!" << std::endl;
	return false;
}


void sendMessagetoUsers(std::string & message, std::map<std::string, std::set<char> > & users )
{

}
// std::string Privmsg::getCommandName() 
// {
// 	return ("PRIVMSG");
// }