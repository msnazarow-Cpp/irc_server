#include "Join.hpp"
Join::Join()
{
}

Join::~Join()
{
}

Join::Join(std::vector<std::string> arguments): Command("JOIN", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Join *Join::create(std::vector<std::string> arguments)
{
	return new Join(arguments);
}

bool Join::execute(Server & server, Client & client)
{
	std::cout << "Join works!" << std::endl;
	return false;
}

// std::string Join::getCommandName() 
// {
// 	return ("JOIN");
// }