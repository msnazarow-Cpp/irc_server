#pragma once
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
class Client{
	public:
		std::string username;
		std::string nickname;
};

class Server{
	public:
	std::string getPassword() const {return ("");}
	std::string getHostname() const {return ("");}
	void authentificate(const Client &client) const {}

	/* std::string clientRespons(Command * command, const Client & client){
		return (":" + client.nickname + "!~" + client.nickname + "@" + getHostname() + " " + command->getCommandMessage() );
	} */
};

class Command
{
private:
	std::string _command_name;
	std::vector<std::string> _arguments;


public:
	
    Command(/* args */);
    Command(std::string command_name, std::vector<std::string> arguments);
	Command(const Command &);
	Command &operator=(const Command &);
    virtual void execute(const Server & server, const Client & client) = 0;
	virtual Command *create(std::vector<std::string> arguments) = 0;
	// virtual std::string getCommandMessage() = 0;
	std::string &getCommandName();
	class WrongArgumentsNumber : public std::exception
	{
		public:
			virtual char const *what() const throw();
	};

	virtual ~Command();
};

enum type
	{
		channel,
		user
	};