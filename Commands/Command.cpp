#include "Command.hpp"

Command::Command(/* args */) {}

Command::Command(const std::string & full_command, const std::string & command_name, const std::vector<std::string> & arguments) : _full_command(full_command), _command_name(command_name), _arguments(arguments),_recipients(10),_recipients_types(10)
{
	
}

std::string &Command::getCommandName() 
{
	return _command_name;
}
Command::~Command()
{

}

const std::string &Command::getCommandMessage() { return _message;}

const std::string &Command::commandName() const { return _command_name; }

std::string Command::fullCommand() const { return _full_command; }

std::vector<std::string> Command::arguments() const { return _arguments; }
