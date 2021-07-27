#pragma once

#include "Command.hpp"

class Userhost: public Command
{
public:
    Userhost();
	Userhost(const std::string & full_command, const std::vector<std::string> & arguments);
    Userhost(const Userhost &);
    Userhost &operator=(const Userhost &);
    ~Userhost();

	virtual Userhost *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
private:
    std::string _newUserhost;
};

