#ifndef __PARCE_H__
#define __PARCE_H__
#include <map>
#include "Command.hpp"
#include "commands_map.hpp"
class Parse
{

private:
	static std::map<std::string, Command*> commands;
	static	Pass * pass;
	static	Kick * kick;
	static	Invite * invite;
	static	Join * join;
	static	Kill * kill;
	static	Mode * mode;
	static	Nick * nick;
	static	Oper * oper;
	static	Part * part;
	static	Privmsg * privmsg;
	static	Quit * quit;
	static	User * user;
public:
	Parse();
	Parse(const Parse &);
	Parse &operator=(const Parse &);
	~Parse();

	static Command *make_command(std::string _message);

	class CommandNotValidExeption : public std::exception
	{
		public:
			virtual char const* what() const throw();
	};


};
#endif // __PARCE_H__