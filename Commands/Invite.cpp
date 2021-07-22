#include "Invite.hpp"
Invite::Invite()
{
}

Invite::~Invite()
{
}

Invite::Invite(std::vector<std::string> arguments): Command("INVITE", arguments)
{
	if (arguments.size() != 2)
		throw WrongArgumentsNumber();
}

Invite *Invite::create(std::vector<std::string> arguments)
{
	return new Invite(arguments);
}

bool Invite::execute(Server & server, Client & client)
{
	std::cout << "Invite works!" << std::endl;
	return false;
}

// std::string Invite::getCommandName() 
// {
// 	return ();
// }