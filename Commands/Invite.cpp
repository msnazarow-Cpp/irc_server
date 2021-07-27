#include "Invite.hpp"
#include "Client.h"
#include "Server.h"
#include <algorithm>
#include "Parse.hpp"

Invite::Invite()
{
}

Invite::~Invite()
{
}

Invite::Invite(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "Invite", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
	if (arguments.size() > 3)
		throw Parse::ThoManyArgs();
	_recipients = ft::split(arguments[0], ',');
	
	_channel_name = arguments[1];
}

Invite *Invite::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Invite(full_command, arguments);
}

bool Invite::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	for (size_t i = 0; i < _recipients.size(); i++)	
	{	
		if (server._users.count(_recipients[i]) == 0)
			client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHNICK,ERR_NOSUCHNICK_MESS),client));
		else if (server._channels.count(_channel_name))
		{
			std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > > & users = server._channels[_channel_name].users;
			server._users[_recipients[i]]->_received_msgs.push(notification("INIVITE :" + _recipients[i]	+ " " + _channel_name, client));
			for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = users.begin(); it != users.end(); it++)
				if ((*it).second.second.count('r') && (*it).first != client.get_nickname())
					server._users[(*it).first]->_received_msgs.push(notification("INIVITE " + _recipients[i] + " :" + _channel_name, client));
		}
	}
	
	std::cout << "Invite works!" << std::endl;
	return false;
}


// void sendMessagetoUsers(std::string & message, std::map<std::string, std::set<char> > & users )
// {

// }
// std::string Invite::getCommandName() 
// {
// 	return ("Invite");
// }