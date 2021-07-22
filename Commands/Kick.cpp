#include "Kick.hpp"
Kick::Kick()
{
}

Kick::~Kick()
{
}

Kick::Kick(std::vector<std::string> arguments): OperatorsCommand("KICK", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kick *Kick::create(std::vector<std::string> arguments)
{
	return new Kick(arguments);
}

bool Kick::execute(Server & server, Client & client)
{
	OperatorsCommand::execute(server, client);
	std::cout << "Kick works!" << std::endl;
	return false;
}

// std::string Kick::getCommandName() 
// {
// 	return ("KICK");
// }