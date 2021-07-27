#pragma once

#include "RegisteredCommand.hpp"

class Notice : public RegisteredCommand
{
public:
    Notice();
	Notice(const std::string & full_command, const std::vector<std::string> & arguments);
    Notice(const Notice &);

    Notice &operator=(const Notice &);
    ~Notice();
	class NosuchUser: public std::exception{};
	class NosuchChannel: public std::exception{};
	class NotJoinYet: public std::exception{};
	class NotHaveWriteRight: public std::exception{};
	virtual Notice *create(const std::string & full_command, const std::vector<std::string> & arguments);
	virtual bool execute(Server & server, Client & client);
private:
	std::string _message;
};

