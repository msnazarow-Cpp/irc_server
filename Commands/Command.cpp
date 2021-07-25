#include "Command.hpp"

Command::Command(/* args */)
{

}

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

char const* Command::WrongArgumentsNumber::what() const throw()
{
	return ("Wrong number of arguments");
}
