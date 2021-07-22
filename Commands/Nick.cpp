#include "Nick.hpp"
#include "Server.h"
Nick::Nick()
{
}

Nick::~Nick()
{
}

Nick::Nick(std::vector<std::string> arguments): Command("NICK", arguments)
{
	if (arguments.size() != 1)
		throw WrongArgumentsNumber();
	_newnick = arguments[0];
}

Nick *Nick::create(std::vector<std::string> arguments)
{
	return new Nick(arguments);
}

bool Nick::execute(Server & server, Client & client)
{
	if (client.status() == unregistered)
		throw NotRegistered();
	if (server.getClients().count(_newnick) == 0)
	{
		server._users[_newnick] = server._users[client.get_nickname()];
		server._to_delete.push(server._users.find(client.get_nickname()));
		client.set_nickname(_newnick);
		client.setStatus(nick_having);
	}
	std::cout << "Nick works!" << std::endl;
	return true;
}

// std::string Nick::getCommandName() 
// {
// 	return ("NICK");
// }