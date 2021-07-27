#pragma once

#include "RegisteredCommand.hpp"

class Quit : public Command
{
public:
    Quit();
	Quit(const std::string & full_command, const std::vector<std::string> & arguments);
    Quit(const Quit &);

    Quit &operator=(const Quit &);
    ~Quit();

	virtual Quit *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
private:
    std::string _message;
};

