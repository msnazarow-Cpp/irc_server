#pragma once

#include "RegisteredCommand.hpp"
class Part : public RegisteredCommand
{
public:
    Part();
	Part(const std::string & full_command, const std::vector<std::string> & arguments);
    Part(const Part &);

    Part &operator=(const Part &);
    ~Part();

	virtual Part *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);

private:
    std::vector<std::string> _channels;
};

