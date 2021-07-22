#pragma once

#include "Command.hpp"

class Privmsg : public Command
{
public:
    Privmsg();
	Privmsg(std::vector<std::string>  arguments);
    Privmsg(const Privmsg &);

    Privmsg &operator=(const Privmsg &);
    ~Privmsg();

	virtual Privmsg *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
	std::string _message;
    std::string _recipient;
	type _recipient_type;
};

