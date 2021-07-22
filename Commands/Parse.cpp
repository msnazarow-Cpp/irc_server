#include "Parse.hpp"
#include "commands_map.hpp"


Parse::Parse() 
{
	commands = create_map<std::string, Command*>
	("PASS", new Pass())("KICK", new Kick())("INVITE", new Invite())("JOIN", new Join())
	("KILL", new Kill())("MODE", new Mode())("NICK", new Nick())("OPER", new Oper())
	("PART", new Part())("PRIVMSG", new Privmsg())("QUIT", new Quit())("USER", new User());
}
// Pass * Parse::pass;
// Kick * Parse::kick;
// Invite * Parse::invite;
// Join * Parse::join;
// Kill * Parse::kill;
// Mode * Parse::mode;
// Nick * Parse::nick;
// Oper * Parse::oper;
// Part * Parse::part;
// Privmsg * Parse::privmsg;
// Quit * Parse::quit;
// User * Parse::user;
// std::map<std::string, Command*> Parse::commands = create_map<std::string, Command*>
// 	("PASS", new Pass())("KICK", new Kick())("INVITE", new Invite())("JOIN", new Join())
// 	("KILL", new Kill())("MODE", new Mode())("NICK", new Nick())("OPER", new Oper())
// 	("PART", new Part())("PRIVMSG", new Privmsg())("QUIT", new Quit())("USER", new User());
// std::map<std::string, Command*> Parse::commands = create_map<std::string, Command*>
// 	("PASS", pass)("KICK", kick)("INVITE", invite)("JOIN", join)
// 	("KILL", kill)("MODE", mode)("NICK", nick)("OPER", oper)
// 	("PART", part)("PRIVMSG", privmsg)("QUIT", quit)("USER", user);
Parse::~Parse() 
{
	std::map<std::string, Command*>::iterator it = commands.begin();
	while (it != commands.end())
	{
		delete (*it).second;
		it++;
	}
}

Parse& Parse::operator=(const Parse &) 
{
	return (*this);
}

char const* Parse::CommandNotValidExeption::what() const throw()
{
	return ("Command not valid");
}

Command *Parse::make_command(std::string _message)
{
	if (_message.empty())
		throw CommandNotValidExeption();

	std::string _command_name;
	std::stringstream _mysteam;
	std::vector<std::string> _arguments(5);
	size_t i = 0;

	_mysteam << _message;
	while (_mysteam >> _arguments[i])
	{
		i++;
		if (i >= _arguments.size())
			_arguments.resize(_arguments.size() * 2);
	}
	_arguments.resize(i);
	if (_arguments.size() == 0)
		throw CommandNotValidExeption();
	_command_name = _arguments[0];
	if (commands.count(_command_name) == 0)
		throw CommandNotValidExeption();
	_arguments.erase(_arguments.begin());
	
	return (commands[_command_name]->create(_arguments));
}