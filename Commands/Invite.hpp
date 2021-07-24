#pragma once

#include "RegisteredCommand.hpp"

class Invite : public RegisteredCommand
{
public:
    Invite();
    Invite(const Invite &);
	Invite(const std::string & full_command, const std::vector<std::string> & arguments);

    Invite &operator=(const Invite &);
    ~Invite();

	virtual Invite *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    
};


