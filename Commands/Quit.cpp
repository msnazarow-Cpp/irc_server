#include "Quit.hpp"
Quit::Quit()
{
}

Quit::~Quit()
{
}

Quit::Quit(std::vector<std::string> arguments): Command("QUIT", arguments)
{
	size_t i = 0;
	while (!arguments[i].empty())
		_message += arguments[i++];
}

Quit *Quit::create(std::vector<std::string> arguments)
{
	return new Quit(arguments);
}

bool Quit::execute(Server & server, Client & client)
{
	std::cout << "Quit works!" << std::endl;
	return true;
}

// std::string Quit::getCommandName() 
// {
// 	return ("QUIT");
// }