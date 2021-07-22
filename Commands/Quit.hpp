#pragma once

#include "Command.hpp"

class Quit : public Command
{
public:
    Quit();
	Quit(std::vector<std::string>  arguments);
    Quit(const Quit &);

    Quit &operator=(const Quit &);
    ~Quit();

	virtual Quit *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    std::string _message;
};

