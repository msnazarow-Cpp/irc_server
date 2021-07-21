#pragma once

#include "Command.hpp"

class Pass : public Command
{
public:
    Pass();
	Pass(std::vector<std::string>  arguments);
    Pass(const Pass &);

    Pass &operator=(const Pass &);
    ~Pass();

	virtual Pass *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();
private:
    std::string _password;
};

