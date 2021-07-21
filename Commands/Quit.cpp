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

void Quit::execute(const Server & server, const Client & client)
{
	std::cout << "Quit works!" << std::endl;
}

// std::string Quit::getCommandName() 
// {
// 	return ("QUIT");
// }