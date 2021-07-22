#pragma once
#include <string>
#include <set>
#include <map>
class Channel {
	public:
    std::string admin;
    std::map<std::string, std::set<char> >  users;
	std::string key;
	std::set<char> priveleges;
};
