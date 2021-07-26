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
	class NothingToDo : public std::exception {};
	class WrongArgumentsNumber : public std::exception{};
	class WrongChannelName : public std::exception{};
	class TryToRegistWithoutPass : public std::exception{};
	class NoNickname : public std::exception{};
	class AlreadyRegistered : public std::exception	{};
	class AleadyPassAuthentificationException : public std::exception {};
	class NotRegistered : public std::exception{};
	virtual ~Command();
	class ErrNickname : public std::exception {};

	const std::string &commandName() const { return _command_name; }

	std::string fullCommand() const { return _full_command; }

	std::vector<std::string> arguments() const { return _arguments; }
};

