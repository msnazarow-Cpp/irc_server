#include "Topic.hpp"
#include "Server.h"
#include "Parse.hpp"
#include "Channel.h"

Topic::Topic()
{
}

Topic::~Topic()
{
}

Topic::Topic(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "Topic", arguments)
{
	
	if (arguments.size() > 2)
		throw Parse::ThoManyArgs();
	if (arguments.size() == 0)
		throw WrongArgumentsNumber();
	if (arguments[0][0] != '#')
		throw WrongChannelName();
	_channel = arguments[0];
	// _channels = ft::split(arguments[0], ',');
	// if (arguments.size() == 2)
	// 	_keys = ft::split(arguments[1], ',');
}

Topic *Topic::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Topic(full_command, arguments);
}
bool Topic::checkBan(std::vector<Channel::BanMask> & ban_list, const std::string & hostIp, Client & client)
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
bool Topic::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	std::string clientName = client.get_nickname();
	if (_channel[0] != '#')
	{
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, _channel + " :"/* +  ERR_NOSUCHCHANNEL_MESS */),client));
	}
	else if(server._channels.count(_channel) == 0)
	{
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, _channel + " " +  ERR_NOSUCHCHANNEL_MESS),client));
	}
	else if (server._channels[_channel].users.count(clientName) == 0)
	{
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOTONCHANNEL, _channel + " " +  ERR_NOTONCHANNEL_MESS),client));
	}
	else if (_arguments.size() == 1)
		{
			if (server._channels[_channel].topic.empty())
				client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_NOTOPIC, _channel + " " +  RPL_NOTOPIC_MESS),client));
			else
				client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_TOPIC, _channel + " :" +  server._channels[_channel].topic),client));
		}
	else
	{
		server._channels[_channel].topic = _arguments[1];
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator  it = server._channels[_channel].users.begin(); it != server._channels[_channel].users.end(); it++)
		{
			server._users[(*it).first]->_received_msgs.push(notification(client, this));
		}
	}
	std::cout << "Topic works!" << std::endl;
	return false;
}

// std::string Topic::getCommandName() 
// {
// 	return ("Topic");
// }