#include "Join.hpp"
#include "Server.h"
#include "Parse.hpp"
#include "Channel.h"

Join::Join()
{
}

Join::~Join()
{
}

Join::Join(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "JOIN", arguments)
{
	if (arguments.size() > 2)
		throw Parse::ThoManyArgs();
	if (arguments.size() == 0)
		throw WrongArgumentsNumber();
	if (arguments[0][0] != '#' || arguments[0].find(' ') != arguments[0].npos)
		throw WrongChannelName();
	_channels = ft::split(arguments[0], ',');
	if (arguments.size() == 2)
		_keys = ft::split(arguments[1], ',');
}

Join *Join::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Join(full_command, arguments);
}
bool Join::checkBan(std::vector<Channel::BanMask> & ban_list, const std::string & hostIp, Client & client)
{
	for (size_t i = 0; i < ban_list.size(); i++)
		if ((ban_list[i].nick == client.get_nickname() || ban_list[i].nick == "*") && 
		(ban_list[i].user == client.get_username() || ban_list[i].user == "*") && 
		(ban_list[i].host == client.get_hostname() || ban_list[i].host == "*"))
		{
			client._received_msgs.push(clientReply(hostIp, Message(ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_MESS),client));
			return true;
		}
	return (false);
}
bool Join::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	std::string clientName = client.get_nickname();
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i][0] != '#')
        {
            client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, _recipients[i] + " :"/* +  ERR_NOSUCHCHANNEL_MESS */),client));
            continue ;
        }
		if(server._channels.count(_channels[i]) == 0)
        {
            server._channels[_channels[i]].creation_time = time(NULL);
            server._channels[_channels[i]].users[clientName].first = server._users[clientName];
            server._users[clientName]->_channels[_channels[i]] = &server._channels[_channels[i]];
            server._channels[_channels[i]].users[clientName].second.insert('w');
            server._channels[_channels[i]].users[clientName].second.insert('r');
            server._channels[_channels[i]].users[clientName].second.insert('o');
        }
		else if (server._channels[_channels[i]].users.count(clientName) == 0)
		{
			std::vector<Channel::BanMask> & ban_list = server._channels[_channels[i]].ban_list;
			if (checkBan(ban_list, server.hostIp(), client) && !client._priveleges.count('O')) // Не пишет сообщение
				continue ;
			server._channels[_channels[i]].users[clientName].first = server._users[clientName];
			server._users[clientName]->_channels[_channels[i]] = &server._channels[_channels[i]];
			server._channels[_channels[i]].users[clientName].second.insert('w');
			server._channels[_channels[i]].users[clientName].second.insert('r');
		}
		
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator  it = server._channels[_channels[i]].users.begin(); it != server._channels[_channels[i]].users.end(); it++)
		{
			server._users[(*it).first]->_received_msgs.push(notification("JOIN :" + _channels[i] ,client));
		}
		_message = "";
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator  it = server._channels[_channels[i]].users.begin(); it != server._channels[_channels[i]].users.end(); it++)
		{
			if ((*it).second.second.count('o'))
				_message += '@';
			_message += (*it).first + " ";
		}
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_NAMREPLY, "= " + _channels[i] + " :" + _message), client));
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_ENDOFNAMES, _channels[i] + " " RPL_ENDOFNAMES_MESS),client));
		if (server._channels[_channels[i]].topic.empty())
			client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_NOTOPIC, _channels[i] + " " +  RPL_NOTOPIC_MESS),client));
		else
			client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_TOPIC, _channels[i] + " :" +  server._channels[_channels[i]].topic),client));
	}
	
	std::cout << "Join works!" << std::endl;
	return false;
}
