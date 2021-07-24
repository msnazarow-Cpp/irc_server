#pragma once

#include "Command.hpp"

class Nick: public Command
{
public:
    Nick();
	Nick(const std::string & full_command, const std::vector<std::string> & arguments);
    Nick(const Nick &)
	;
    Nick &operator=(const Nick &);
    ~Nick();

	virtual Nick *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::string _newnick;
};

