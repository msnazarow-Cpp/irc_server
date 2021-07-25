#pragma once

#include "RegisteredCommand.hpp"

class Notice : public RegisteredCommand
{
public:
    Notice();
	Notice(const std::string & full_command, const std::vector<std::string> & arguments);
    Notice(const Notice &);

    Notice &operator=(const Notice &);
    ~Notice();
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
	virtual Notice *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
	std::string _message;
};

