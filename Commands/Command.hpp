#pragma once
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include "codes.hpp"
class Server;
class Client;

// class Client{
// 	public:
// 		std::string username;
// 		std::string nickname;
// };

// class Server{
// 	public:
// 	const std::string &getPassword() const {return ("");}
// 	const std::string &getHostname() const {return ("");}
// 	void authentificate(const Client &client) const {}

// 	/* std::string clientRespons(Command * command, const Client & client){
// 		return (":" + client.nickname + "!~" + client.nickname + "@" + getHostname() + " " + command->getCommandMessage() );
// 	} */
// };
enum type
	{
		channel,
		user
	};
class Command
{
protected:
	std::string _full_command;
	std::string _command_name;
	std::string _message;
	std::vector<std::string> _arguments;
	std::vector<std::string> _recipients;
	std::vector<type> _recipients_types;
	//std::vector<std::pair< std::string, type> > _recipients;
public:
	Command(/* args */);
	Command(const std::string & full_command, const std::string & command_name, const std::vector<std::string> & arguments);
	Command(const Command &);
	Command &operator=(const Command &);
	virtual bool execute(Server &server, Client &client) = 0;
	virtual Command *create(const std::string & full_command, const std::vector<std::string> & arguments) = 0;
	virtual const std::string &getCommandMessage() { return _message;}
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
	class ErrNickname : public std::exception {};

	const std::string &commandName() const { return _command_name; }

	std::string fullCommand() const { return _full_command; }

	std::vector<std::string> arguments() const { return _arguments; }
};

