#include "Oper.hpp"
#include "Client.h"
#include "Server.h"
Oper::Oper()
{
}

Oper::~Oper()
{
}

Oper::Oper(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "OPER", arguments)
{
	if (arguments.size() != 2)
		throw WrongArgumentsNumber();
}

Oper *Oper::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Oper(full_command, arguments);
}

bool Oper::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);
	if (client._priveleges.count('O'))
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MESS),client));
	else if (_arguments[0] == "oper" && _arguments[1] == "school21")
	{
		client._priveleges.insert('O');
		// :irc.example.net MODE joj :+o
		client._received_msgs.push(":" + server.hostIp() + " MODE " + client.get_nickname() + " :+o\r\n");
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_YOUREOPER,RPL_YOUREOPER_MESS),client));
	}
	else 
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_PASSWDMISMATCH,ERR_PASSWDMISMATCH_MESS),client));

	std::cout << "Oper works!" << std::endl;
	return false;
}

// std::string Oper::getCommandName() 
// {
// 	return ("OPER");
// }