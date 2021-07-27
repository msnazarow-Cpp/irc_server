#ifndef __PARCE_H__
#define __PARCE_H__
#include <map>
#include "Command.hpp"
#include "commands_map.hpp"
class Parse
{

private:
	std::map<std::string, Command*> commands;
public:
	Parse();
	Parse(const Parse &);
	Parse &operator=(const Parse &);
	~Parse();

	SharedPtr<Command> make_command(std::string _message, Client *client);

	class UknownCommand : public std::exception{};
	class ThoManyArgs : public std::exception{};
	class Spaces : public std::exception{};
};
#endif // __PARCE_H__