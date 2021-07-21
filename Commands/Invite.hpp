#pragma once

#include "Command.hpp"

class Invite : public Command
{
public:
    Invite();
    Invite(const Invite &);
	Invite(std::vector<std::string> arguments);

    Invite &operator=(const Invite &);
    ~Invite();

	virtual Invite *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();
private:
    
};


