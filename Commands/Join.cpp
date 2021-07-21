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

void Join::execute(const Server & server, const Client & client)
{
	std::cout << "Join works!" << std::endl;
}

// std::string Join::getCommandName() 
// {
// 	return ("JOIN");
// }