#include "Invite.hpp"
Invite::Invite()
{
}

Invite::~Invite()
{
}

Invite::Invite(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "INVITE", arguments)
{
	if (arguments.size() != 2)
		throw WrongArgumentsNumber();
}

Invite *Invite::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Invite(full_command, arguments);
}

bool Invite::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	std::cout << "Invite works!" << std::endl;
	return false;
}

// std::string Invite::getCommandName() 
// {
// 	return ();
// }