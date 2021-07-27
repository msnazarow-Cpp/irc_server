#pragma once

#include "Command.hpp"

class Pass : public Command
{
public:
    Pass();
	Pass(const std::string & full_command, const std::vector<std::string> & arguments);
    Pass(const Pass &);

    Pass &operator=(const Pass &);
    ~Pass();
    class PasswordWrongExcetion: public std::exception{};
	virtual Pass *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
private:
    std::string _password;
};

