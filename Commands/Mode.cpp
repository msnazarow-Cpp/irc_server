#include "Mode.hpp"
Mode::Mode()
{
}

Mode::~Mode()
{
}

Mode::Mode(std::vector<std::string> arguments): Command("MODE", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Mode *Mode::create(std::vector<std::string> arguments)
{
	return new Mode(arguments);
}

void Mode::execute(const Server & server, const Client & client)
{
	std::cout << "Mode works!" << std::endl;
}

// std::string Mode::getCommandName() 
// {
// 	return ("MODE");
// }