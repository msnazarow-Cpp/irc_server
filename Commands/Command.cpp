#include "Command.hpp"

Command::Command(/* args */)
{
}
Command::Command(std::string command_name, std::vector<std::string> arguments) :_command_name(command_name), _arguments(arguments)
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
