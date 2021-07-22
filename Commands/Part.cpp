#include "Part.hpp"
Part::Part()
{
}

Part::~Part()
{
}

Part::Part(std::vector<std::string> arguments): Command("PART", arguments)
{
	if (arguments.size() < 1)
		throw WrongArgumentsNumber();
}

Part *Part::create(std::vector<std::string> arguments)
{
	return new Part(arguments);
}

bool Part::execute(Server & server, Client & client)
{
	std::cout << "Part works!" << std::endl;
	return false;
}

// std::string Part::getCommandName() 
// {
// 	return ("PART");
// }