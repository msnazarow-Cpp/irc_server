#pragma once
#include <string>
#include "utils.h"
class Message
{
public:
	Message();
	Message(const std::string & message);
//	Message(std::string message);
	Message(const std::string &code, const std::string & message);
	Message(const Message &);
	Message &operator=(const Message &);
	~Message();

	std::string code() const { return _code; }

	const std::string &message() const { return _message; }

private:
	std::string _code;
	std::string _message;
};
