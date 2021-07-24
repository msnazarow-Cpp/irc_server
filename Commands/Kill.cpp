#include "Kill.hpp"
Kill::Kill()
{
}

Kill::~Kill()
{
}

Kill::Kill(const std::string & full_command, const std::vector<std::string> & arguments): OperatorsCommand(full_command, "KILL", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Kill *Kill::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Kill(full_command, arguments);
}

bool Kill::execute(Server & server, Client & client)
{
	OperatorsCommand::execute(server, client);
	std::cout << "Kill works!" << std::endl;
	return true;
}

// std::string Kill::getCommandName() 
// {
// 	return ("KILL");
// }