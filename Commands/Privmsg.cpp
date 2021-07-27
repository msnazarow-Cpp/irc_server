#include "Privmsg.hpp"
#include "Client.h"
#include "Server.h"
#include <algorithm>
#include "Parse.hpp"

Privmsg::Privmsg()
{
}

Privmsg::~Privmsg()
{
}

Privmsg::Privmsg(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "PRIVMSG", arguments)
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

Privmsg *Privmsg::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Privmsg(full_command, arguments);
}

bool Privmsg::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	for (size_t i = 0; i < _recipients.size(); i++)	
	{	
		if (_recipients_types[i] == user)
		{
			if (server._users.count(_recipients[i]) == 0)
				client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHNICK,ERR_NOSUCHNICK_MESS),client));
			else
				server._users[_recipients[i]]->_received_msgs.push(notification("PRIVMSG " + _recipients[i]	+ " :" + _message, client));
		}
		else
		{
			if(server._channels.count(_recipients[i]) == 0)
				{
					client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHNICK,ERR_NOSUCHNICK_MESS),client));
					continue;
				}
			std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > > & users = server._channels[_recipients[i]].users;
			if (users.count(client.get_nickname()) == 0)
			{
				client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, _recipients[i] + " " +  ERR_NOSUCHCHANNEL_MESS),client));
			}	
			else if (users[client.get_nickname()].second.count('w') == 0)
				throw NotHaveWriteRight();
			else
			{
				for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = users.begin(); it != users.end(); it++)
					if ((*it).second.second.count('r') && (*it).first != client.get_nickname())
						server._users[(*it).first]->_received_msgs.push(notification("PRIVMSG " + _recipients[i] + " :" + _message, client));
			}
		}
	}
	
	std::cout << "Privmsg works!" << std::endl;
	return false;
}


// void sendMessagetoUsers(std::string & message, std::map<std::string, std::set<char> > & users )
// {

// }
// std::string Privmsg::getCommandName() 
// {
// 	return ("PRIVMSG");
// }