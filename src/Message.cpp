#include "Message.h"

Message::Message()
{
}

Message::Message(const Message &)
{
	
}

Message::Message(const std::string & code, const std::string & message): _code(code), _message(message)
{
	
}

Message::Message(const std::string & message): _message(message)
{
	
}
Message &Message::operator=(const Message &) {
	return (*this);
}

Message::~Message()
{
}

std::string Message::code() const { return _code; }

const std::string &Message::message() const { return _message; }
