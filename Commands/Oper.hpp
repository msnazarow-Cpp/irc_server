#pragma once

#include "RegisteredCommand.hpp"

class Oper: public RegisteredCommand
{
public:
    Oper();
	Oper(const std::string & full_command, const std::vector<std::string> & arguments);
    Oper(const Oper &);

    Oper &operator=(const Oper &);
    ~Oper();

	virtual Oper *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);

private:
    
};

