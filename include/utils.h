#pragma once

# include <vector>
# include <map>
# include <string>
# include <exception>
# include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace ft {
    bool isalldigits(const std::string &str);

    void ws_to_tab(std::string &str);

    void trim(std::string &str, char c);

    std::vector<std::string> split(const std::string &str, const char delim);

    std::istream &getline(std::istream &ifs, std::string &line);

    template <typename T>
    std::string to_string(T x)
    {
    	std::ostringstream ostr;
    	ostr << x;
		return ostr.str();
    }
    template<typename T>
    std::string to_str(T n) {
    	std::string res;
    	std::stringstream ss;
    	if (!(ss << n) || !(ss >> res))
    		throw std::runtime_error("Conversion impossible");
    	//TODO: do we need exception?
    	return res;
    }
    std::vector<std::string> split(const std::string& str, const std::string& delim);

    size_t to_num(const std::string &str, bool hex = false);

    std::string toupper(std::string data);

    std::string tolower(std::string data);
} //namespace ft

