#pragma once

#include "RegisteredCommand.hpp"

class Privmsg : public RegisteredCommand
{
public:
    Privmsg();
	Privmsg(std::vector<std::string>  arguments);
    Privmsg(const Privmsg &);

    Privmsg &operator=(const Privmsg &);
    ~Privmsg();
	class NosuchUser: public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return ("No such User");
			}
	};
	class NosuchChannel: public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return ("No such Channel");
			}
	};
	class NotJoinYet: public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return ("You mast join channel before write to it");
			}
	};
	class NotHaveWriteRight: public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return ("You do not have right to write in this channel");
			}
	};
	virtual Privmsg *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
	std::string _message;
    std::string _recipient;
	type _recipient_type;
};

