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
    class PasswordWrongExcetion: public std::exception
    {
		public: 
        virtual const char * what() const throw()
        {
            return("Wrong Server Password");
        }
    };
	virtual Pass *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
	// virtual const std::string &getCommandName();
private:
    std::string _password;
};

