#pragma once

class Channel {
    std::string admin;
    std::map<std::string nick, Privliges>  users;
};
