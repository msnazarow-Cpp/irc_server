#include "Mode.hpp"
Mode::Mode()
{
}

Mode::~Mode()
{
}

Mode::Mode(std::vector<std::string> arguments): OperatorsCommand("MODE", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Mode *Mode::create(std::vector<std::string> arguments)
{
	return new Mode(arguments);
}

bool Mode::execute(Server & server, Client & client)
{
	OperatorsCommand::execute(server, client);
	std::cout << "Mode works!" << std::endl;
	return false;
}

// std::string Mode::getCommandName() 
// {
// 	return ("MODE");
// }