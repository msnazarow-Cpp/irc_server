#pragma once
#include <cstring>
#include <vector>
#include <map>
class Channel {
    std::string admin;
    std::map<std::string, std::vector<char>>  users;
};
