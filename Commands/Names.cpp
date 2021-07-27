#include "Names.hpp"
#include "Server.h"
#include "Parse.hpp"
#include "Channel.h"

Names::Names()
{
}

Names::~Names()
{
}

Names::Names(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "Names", arguments)
{
	if (arguments.size() > 2)
		throw Parse::ThoManyArgs();
	if (arguments.size() == 0)
		throw WrongArgumentsNumber();
	if (arguments[0][0] != '#')
		throw WrongChannelName();
	_channels = ft::split(arguments[0], ',');
	if (arguments.size() == 2)
		_keys = ft::split(arguments[1], ',');
}

Names *Names::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Names(full_command, arguments);
}
bool Names::checkBan(std::vector<Channel::BanMask> & ban_list, const std::string & hostIp, Client & client)
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
bool Names::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	std::string clientName = client.get_nickname();
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i][0] != '#' || server._channels.count(_channels[i]) == 0)
			{
				client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, _recipients[i] + " :"/* +  ERR_NOSUCHCHANNEL_MESS */),client));
				continue ;
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
	}
	
	std::cout << "Names works!" << std::endl;
	return false;
}
