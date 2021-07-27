#pragma once

#include "Command.hpp"

class Ison: public Command
{
public:
    Ison();
	Ison(const std::string & full_command, const std::vector<std::string> & arguments);
    Ison(const Ison &)
	;
    Ison &operator=(const Ison &);
    ~Ison();

	virtual Ison *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);

private:
    std::string _newIson;
};

