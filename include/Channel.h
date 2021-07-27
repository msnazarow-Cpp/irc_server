#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
#include "SharedPtr.h"
#include "Client.h"

class Channel
{
public:
	struct BanMask
	{
		std::string nick;
		std::string user;
		std::string host;
		std::string operator_name;
		time_t		time;
	};
	
	size_t creation_time;
	std::string topic;
    std::string admin;
    std::map<std::string,std::pair<SharedPtr<Client>,std::set<char> > > users;
	std::vector<BanMask> ban_list;
	std::string key;
	std::set<char> priveleges;
	Channel();
	Channel(const Channel &);
	Channel &operator=(const Channel &);
	~Channel();

	const std::string &getTopic() const;

private:
	
};
