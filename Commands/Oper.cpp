#include "Oper.hpp"
Oper::Oper()
{
}

Oper::~Oper()
{
}

Oper::Oper(std::vector<std::string> arguments): Command("OPER", arguments)
{
	if (arguments.size() < 2)
		throw WrongArgumentsNumber();
}

Oper *Oper::create(std::vector<std::string> arguments)
{
	return new Oper(arguments);
}

void Oper::execute(const Server & server, const Client & client)
{
	std::cout << "Oper works!" << std::endl;
}

// std::string Oper::getCommandName() 
// {
// 	return ("OPER");
// }