#pragma once

#include "Command.hpp"

class User : public Command
{ 
public:
    User();
	User(std::vector<std::string>  arguments);
    User(const User &);

    User &operator=(const User &);
    ~User();

	virtual User *create(std::vector<std::string> arguments);
	virtual void execute(const Server & server, const Client & client);
	// virtual std::string getCommandName();
private:
    std::string _username;
	std::string _hostname;
	std::string _servername;
	std::string _realname;
};

