#pragma once

#include "Command.hpp"

class Nick: public Command
{
public:
    Nick();
	Nick(std::vector<std::string>  arguments);
    Nick(const Nick &)
	;
    Nick &operator=(const Nick &);
    ~Nick();

	virtual Nick *create(std::vector<std::string> arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual std::string getCommandName();
private:
    std::string _newnick;
};

