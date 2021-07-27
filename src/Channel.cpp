
#include "Channel.h"

Channel::Channel()
{ 
}

Channel::~Channel()
{
}
Channel::Channel(const Channel &)
	: admin(),
	  users(),
	  key(),
	  priveleges()
{
	
}

const std::string &Channel::getTopic() const { return topic; }
