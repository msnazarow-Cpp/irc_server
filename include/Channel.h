#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
class Client;

class Channel
{
public:
	std::string topic;
    std::string admin;
    std::map<std::string,std::pair<Client *,std::set<char> > > users;
	std::vector<std::string> ban_list;
	std::string key;
	std::set<char> priveleges;
	Channel();
	Channel(const Channel &);
	Channel &operator=(const Channel &);
	~Channel();

	const std::string &getTopic() const { return topic; }

private:
	
};
