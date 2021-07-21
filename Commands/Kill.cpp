#include "Kill.hpp"
Kill::Kill()
{
}

Kill::~Kill()
{
}

Kill::Kill(std::vector<std::string> arguments): Command("KILL", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kill *Kill::create(std::vector<std::string> arguments)
{
	return new Kill(arguments);
}

void Kill::execute(const Server & server, const Client & client)
{
	std::cout << "Kill works!" << std::endl;
}

// std::string Kill::getCommandName() 
// {
// 	return ("KILL");
// }