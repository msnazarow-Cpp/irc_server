#pragma once
#include <string>
#include "utils.h"
struct Message {
    Message(const std::string &from, const std::string &data) : from(from), data(data) {
        time = 0;
    }
    std::string from;
    std::string data;
    int time;
    
    std::string to_string() {
        return "[" + SSTR(time) + "] " + from + " :" + data;
    }
};
