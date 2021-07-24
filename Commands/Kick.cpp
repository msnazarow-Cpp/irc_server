#include "Kick.hpp"
Kick::Kick()
{
}

Kick::~Kick()
{
}

Kick::Kick(const std::string & full_command, const std::vector<std::string> & arguments): OperatorsCommand(full_command, "KICK", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kick *Kick::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Kick(full_command, arguments);
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