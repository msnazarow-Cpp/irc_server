#include "Kick.hpp"
Kick::Kick()
{
}

Kick::~Kick()
{
}

Kick::Kick(std::vector<std::string> arguments): Command("KICK", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kick *Kick::create(std::vector<std::string> arguments)
{
	return new Kick(arguments);
}

void Kick::execute(const Server & server, const Client & client)
{
	std::cout << "Kick works!" << std::endl;
}

// std::string Kick::getCommandName() 
// {
// 	return ("KICK");
// }