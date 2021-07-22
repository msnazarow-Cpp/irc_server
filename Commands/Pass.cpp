#include "Pass.hpp"
#include "Server.h"
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
	_password = arguments[0];
}

Pass *Pass::create(std::vector<std::string> arguments)
{
	return new Pass(arguments);
}

bool Pass::execute(Server & server, Client & client)
{
	if (client.status() == registered_user)
		throw AlreadyRegistered();
	if (client.status() >= pass_passing)
        throw AleadyPassAuthentificationException();
	if (server.getPassword() == _password)
  	{
		client.setStatus(pass_passing);
		client._received_msgs.push(returnSendableMessageToClient("Correct password", client));
	}
	else
		throw Pass::PasswordWrongExcetion();
	std::cout << "Pass works!" << std::endl;
	return false;
}

// std::string Pass::getCommandName() 
// {
// 	return ("PASS");
// }