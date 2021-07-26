#pragma once
#include "Command.hpp"
#include "Invite.hpp"
#include "Join.hpp"
#include "Kick.hpp"
#include "Kill.hpp"
#include "Mode.hpp"
#include "Nick.hpp"
#include "Oper.hpp"
#include "Part.hpp"
#include "Pass.hpp"
#include "Privmsg.hpp"
#include "Quit.hpp"
#include "User.hpp"
#include "List.hpp"
#include "Who.hpp"
#include "Notice.hpp"
#include "Whois.hpp"
#include "Ison.hpp"
#include "Topic.hpp"
#include "Names.hpp"
template <typename T, typename U>
class create_map
{
private:
    std::map<T, U> m_map;
public:
    create_map(const T& key, const U& val)
    {
        m_map[key] = val;
    }

    create_map<T, U>& operator()(const T& key, const U& val)
    {
        m_map[key] = val;
        return *this;
    }

    operator std::map<T, U>()
    {
        return m_map;
    }
};


