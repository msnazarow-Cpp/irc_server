#include "User.hpp"
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
	while (!arguments[i].empty())
		_realname += arguments[i++];
}

User *User::create(std::vector<std::string> arguments)
{
	return new User(arguments);
}

void User::execute(const Server & server, const Client & client)
{
	std::cout << "User works!" << std::endl;
}

// std::string User::getCommandName() 
// {
// 	return ("USER");
// }