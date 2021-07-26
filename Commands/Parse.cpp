#include "Parse.hpp"
#include "commands_map.hpp"
#include "Client.h"

Parse::Parse() 
{
	commands = create_map<std::string, Command*>
	("PASS", new Pass())("KICK", new Kick())("INVITE", new Invite())("JOIN", new Join())
	("KILL", new Kill())("MODE", new Mode())("NICK", new Nick())("OPER", new Oper())
	("PART", new Part())("PRIVMSG", new Privmsg())("QUIT", new Quit())("USER", new User())
	("LIST", new List())("WHO", new Who())("NOTICE", new Notice())("ISON", new Ison())
	("WHOIS", new Whois())("TOPIC", new Topic())("NAMES", new Names())("USERHOST", new Userhost());
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

void removeSpaces(std::string& str)
{
	size_t n = 0;
	while (isspace(str[n]))
		n++;
	str.erase(str.begin(), str.begin() + n);
	for (std::string::iterator it = str.begin(); it != str.end(); it++)    
	{
		std::string::iterator begin = it;        
		while (it != str.end() && ::isspace(*it) )
			it++;
		if (it - begin > 1)            
			it = str.erase(begin + 1, it) - 1;
	}
}

SharedPtr<Command> Parse::make_command(std::string _message, Client* client)
{
	if (_message.empty())
		throw UknownCommand();

	std::string _full_command;// = _message;
	std::string _command_name;
	std::string _last_argument;
	std::stringstream _mysteam;
	std::vector<std::string> _arguments(5);
	size_t i = 0;
	size_t pos = _message.find(':');
	if (pos != _message.npos)
		_last_argument = _message.substr(pos + 1, _message.size() - pos);
	removeSpaces(_last_argument);
	_message = _message.substr(0, pos);
	_mysteam << _message;
	while (_mysteam >> _arguments[i])
	{
		if (i == 0)
		{
			_command_name = _arguments[i];
			for (size_t j = 0; j < _command_name.length(); j++)
				_command_name[j] = toupper(_command_name[j]);
			if (commands.count(_command_name) == 0)
				throw UknownCommand();
			else
				client->touch_check = true;
		}
		i++;	
		if (i >= _arguments.size())
			_arguments.resize(_arguments.size() * 2);
		if (i > 5)
			throw ThoManyArgs();
	}
	_arguments.resize(i);
	if (_arguments.size() == 0)
		throw Spaces();
	
	_arguments.erase(_arguments.begin());
	if (pos != _message.npos)
		_arguments.push_back(_last_argument);
	
	_full_command = _message + " :" + _last_argument;
	return (SharedPtr<Command> (commands[_command_name]->create(_full_command, _arguments)) );
}