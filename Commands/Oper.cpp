#include "Oper.hpp"
Oper::Oper()
{
}

Oper::~Oper()
{
}

Oper::Oper(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "OPER", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Oper *Oper::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Oper(full_command, arguments);
}

bool Oper::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	std::cout << "Oper works!" << std::endl;
	return false;
}

// std::string Oper::getCommandName() 
// {
// 	return ("OPER");
// }