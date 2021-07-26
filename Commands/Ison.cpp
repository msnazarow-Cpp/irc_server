#include "Ison.hpp"
#include "Server.h"
#include "Parse.hpp"
Ison::Ison()
{
}

Ison::~Ison()
{
}

Ison::Ison(const std::string & full_command, const std::vector<std::string> & arguments): Command(full_command, "Ison", arguments)
{
	if (arguments.size() < 1)
		throw WrongArgumentsNumber();
}

Ison *Ison::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Ison(full_command, arguments);
}

bool Ison::execute(Server & server, Client & client)
{
	client.touch_check = true;
	_message = "";
	// for (Server::Clients_map::iterator it_ch = server._users.begin(); it_ch != server._users.end(); it_ch++)
	for (size_t i = 0; i < _arguments.size(); i++)
	{
		if (server._users.count(_arguments[i]))
			_message += _arguments[i] + " ";
	}
	
		
	client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_ISON, _message),client));
	return true;
}

// std::string Ison::getCommandName() 
// {
// 	return ("Ison");
// }