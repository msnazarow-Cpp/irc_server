#pragma once

#include "Command.hpp"

class Oper: public Command
{
public:
    Oper();
	Oper(std::vector<std::string>  arguments);
    Oper(const Oper &);

    Oper &operator=(const Oper &);
    ~Oper();

	virtual Oper *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();

private:
    
};
