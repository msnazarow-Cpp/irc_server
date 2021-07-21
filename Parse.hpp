#ifndef __PARCE_H__
#define __PARCE_H__
#include <map>
#include "Command.hpp"
class Parse
{

private:
	std::map<std::string, Command*> commands;

public:
	Parse();
	Parse(const Parse &);
	Parse &operator=(const Parse &);
	~Parse();

	Command *make_command(std::string _message);

	class CommandNotValidExeption : public std::exception
	{
		public:
			virtual char const* what() const throw();
	};


};
#endif // __PARCE_H__