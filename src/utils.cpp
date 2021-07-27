#include <sstream>
#include <algorithm>
#include "utils.h"

std::vector<std::string> ft::split(const std::string &str, const char delim) {
	size_t start;
	size_t end = 0;
	std::vector<std::string> res;

	while (end != std::string::npos) {
		start = str.find_first_not_of(delim, end);
		end = str.find_first_of(delim, start);
		if (start != std::string::npos || end != std::string::npos)
			res.push_back(str.substr(start, end - start));
	}
	return res;
}

std::vector<std::string> ft::split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
