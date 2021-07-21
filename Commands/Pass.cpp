#include "Pass.hpp"
Pass::Pass()
{
}

Pass::~Pass()
{
}

Pass::Pass(std::vector<std::string> arguments): Command("PASS", arguments)
{
	if (arguments.size() != 1)
		throw WrongArgumentsNumber();
	_password = 1;
}

Pass *Pass::create(std::vector<std::string> arguments)
{
	return new Pass(arguments);
}

void Pass::execute(const Server & server, const Client & client)
{
	if (server.getPassword() == _password)
		server.authentificate(client);
	std::cout << "Pass works!" << std::endl;
}

// std::string Pass::getCommandName() 
// {
// 	return ("PASS");
// }