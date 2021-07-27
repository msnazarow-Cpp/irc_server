#pragma once

#include "Command.hpp"

class User : public Command
{ 
public:
    User();
	User(const std::string & full_command, const std::vector<std::string> & arguments);
    User(const User &);

    User &operator=(const User &);
    ~User();

	virtual User *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
private:
    std::string _username;
	std::string _realname;
};

