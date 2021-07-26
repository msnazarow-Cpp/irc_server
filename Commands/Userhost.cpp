#include "Userhost.hpp"
#include "Server.h"
#include "Parse.hpp"
Userhost::Userhost()
{
}

Userhost::~Userhost()
{
}

Userhost::Userhost(const std::string & full_command, const std::vector<std::string> & arguments): Command(full_command, "Userhost", arguments)
{
	if (arguments.size() < 1)
		throw WrongArgumentsNumber();
}

Userhost *Userhost::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Userhost(full_command, arguments);
}

bool Userhost::execute(Server & server, Client & client)
{
	client.touch_check = true;
	_message = "";
	if (!server._users.count(_arguments[0]))
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHNICK,ERR_NOSUCHNICK_MESS),client));
	else
	{
		_message = ":" + server._users[_arguments[0]]->get_nickname() + "=+" + server._users[_arguments[0]]->get_username() + "@" + server._users[_arguments[0]]->get_hostname();	
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_USERHOST, _message),client));
	}
	return true;
}

// std::string Userhost::getCommandName() 
// {
// 	return ("Userhost");
// }