
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
