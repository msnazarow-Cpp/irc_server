#pragma once

#include "RegisteredCommand.hpp"

class Oper: public RegisteredCommand
{
public:
    Oper();
	Oper(std::vector<std::string>  arguments);
    Oper(const Oper &);

    Oper &operator=(const Oper &);
    ~Oper();

	virtual Oper *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();

private:
    
};

