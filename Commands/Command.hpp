#pragma once
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
class Server;
class Client;

// class Client{
// 	public:
// 		std::string username;
// 		std::string nickname;
// };

// class Server{
// 	public:
// 	std::string getPassword() const {return ("");}
// 	std::string getHostname() const {return ("");}
// 	void authentificate(const Client &client) const {}

// 	/* std::string clientRespons(Command * command, const Client & client){
// 		return (":" + client.nickname + "!~" + client.nickname + "@" + getHostname() + " " + command->getCommandMessage() );
// 	} */
// };

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
	virtual bool execute(Server &server, Client &client) = 0;
	virtual Command *create(std::vector<std::string> arguments) = 0;
	std::string getCommandMessage() { return "command"; }
	std::string &getCommandName();
	class WrongArgumentsNumber : public std::exception
	{
	public:
		virtual char const *what() const throw();
	};
		class WrongChannelName : public std::exception
	{
	public:
		virtual char const *what() const throw()
		{
			return ("Wrong channel name");
		}
	};
	class TryToRegistWithoutPass : public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return("You should enter server password before you can registrate");
			}
	};
	class NoNickname : public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return("You should enter your nickname before you can set username");
			}
	};
	class AlreadyRegistered : public std::exception
	{
		public:
			virtual char const *what() const throw()
			{
				return("You have already regiseter");
			}
	};
	class AleadyPassAuthentificationException : public std::exception
    {
        public:
			virtual char const* what() const throw()
            {
                return("You already input right password. Use NICK and USER to pass registration");
            }
    };
	class NotRegistered : public std::exception
	{
		public:
			virtual char const* what() const throw()
            {
                return("You are not registered");
            }
	};
	virtual ~Command();
};

enum type
{
	channel,
	user
};