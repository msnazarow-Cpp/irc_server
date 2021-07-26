#pragma once

#include "RegisteredCommand.hpp"

class Privmsg : public RegisteredCommand
{
public:
    Privmsg();
	Privmsg(const std::string & full_command, const std::vector<std::string> & arguments);
    Privmsg(const Privmsg &);

    Privmsg &operator=(const Privmsg &);
    ~Privmsg();
	class NosuchUser: public std::exception{};
	class NosuchChannel: public std::exception{};
	class NotJoinYet: public std::exception{};
	class NotHaveWriteRight: public std::exception{};
	virtual Privmsg *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
	std::string _message;
};

