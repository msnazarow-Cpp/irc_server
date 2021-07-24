#pragma once

#include "RegisteredCommand.hpp"

class Quit : public RegisteredCommand
{
public:
    Quit();
	Quit(const std::string & full_command, const std::vector<std::string> & arguments);
    Quit(const Quit &);

    Quit &operator=(const Quit &);
    ~Quit();

	virtual Quit *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::string _message;
};

