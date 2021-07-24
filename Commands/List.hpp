#pragma once

#include "RegisteredCommand.hpp"

class List : public RegisteredCommand
{
public:
    List();
	List(const std::string & full_command, const std::vector<std::string> & arguments);
    List(const List &);

    List &operator=(const List &);
    ~List();

	virtual List *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::string _message;
};

