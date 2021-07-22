#include "User.hpp"
#include "Client.h"
User::User()
{
}

User::~User()
{
}

User::User(std::vector<std::string> arguments): Command("USER", arguments)
{
	if (arguments.size() < 4)
		throw WrongArgumentsNumber();
	_username = arguments[0];
	_hostname = arguments[1];
	_servername = arguments[2];
	_realname = arguments[3];
	size_t i = 4;
	while (i < arguments.size())
		_realname += arguments[i++];
}

User *User::create(std::vector<std::string> arguments)
{
	return new User(arguments);
}

bool User::execute(Server & server, Client & client)
{
	if (client.status() == unregistered)
		throw NotRegistered();
	if (client.status() < nick_having)
		throw NoNickname();
	if (client.status() == registered_user)
		throw AlreadyRegistered();
	std::cout << "User works!" << std::endl;
	return false;
}

// std::string User::getCommandName() 
// {
// 	return ("USER");
// }