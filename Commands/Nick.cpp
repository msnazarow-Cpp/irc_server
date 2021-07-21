#include "Nick.hpp"
Nick::Nick()
{
}

Nick::~Nick()
{
}

Nick::Nick(std::vector<std::string> arguments): Command("NICK", arguments)
{
	if (arguments.size() != 1)
		throw WrongArgumentsNumber();
}

Nick *Nick::create(std::vector<std::string> arguments)
{
	return new Nick(arguments);
}

void Nick::execute(const Server & server, const Client & client)
{
	std::cout << "Nick works!" << std::endl;
}

// std::string Nick::getCommandName() 
// {
// 	return ("NICK");
// }