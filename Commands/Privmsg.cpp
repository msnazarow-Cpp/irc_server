#include "Privmsg.hpp"
Privmsg::Privmsg()
{
}

Privmsg::~Privmsg()
{
}

Privmsg::Privmsg(std::vector<std::string> arguments): Command("PRIVMSG", arguments)
{
	if (arguments.size() < 3)
		throw WrongArgumentsNumber();
	if (arguments[0][0] == '#')
		_recipient_type = channel;
	else
		_recipient_type = user;
	size_t i = 1;
	while (!arguments[i].empty())
		_message += arguments[i++];
}

Privmsg *Privmsg::create(std::vector<std::string> arguments)
{
	return new Privmsg(arguments);
}

bool Privmsg::execute(Server & server, Client & client)
{
	std::cout << "Privmsg works!" << std::endl;
	return false;
}

// std::string Privmsg::getCommandName() 
// {
// 	return ("PRIVMSG");
// }