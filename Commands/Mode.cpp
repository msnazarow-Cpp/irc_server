#include "Mode.hpp"
#include "Client.h"
#include "Server.h"

Mode::Mode()
{
}

Mode::~Mode()
{
}

Mode::Mode(const std::string & full_command, const std::vector<std::string> & arguments): OperatorsCommand(full_command, "MODE", arguments)
{
	if (arguments.size() == 0)
		throw WrongArgumentsNumber();
	_recipients[0] = arguments[0];
	if (_recipients[0][0] == '#')
		_recipients_types[0] = channel;
	else
		_recipients_types[0] = user;
}

Mode *Mode::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Mode(full_command, arguments);
}

std::vector<std::string> Mode::banparse(const std::string &ban)
{
	std::vector<std::string> out(3);
	size_t pos1 = ban.find('!');
	out[0] = ban.substr(0, pos1);
	if (pos1 != ban.npos)
	{
		size_t pos2 = ban.find('@');
		out[1] = ban.substr(pos1 + 1, pos2 - pos1);
		if (pos2 != ban.npos)
			out[2] = ban.substr(pos2 + 1, ban.size() - pos2);
		else 
			out[2] = "*";
	}
	else{
		out[1] = out[2] = "*";
	}
	return (out);
}
bool Mode::banCase(Server & server, Client & client)
{
	std::vector<std::string> banlist; 
	std::vector<Channel::BanMask> & _ban_list = server._channels[_recipients[0]].ban_list;
	if (_arguments.size() == 2)
	{
		for (size_t i = 0; i < _ban_list.size(); i++)
			banlist.push_back(_ban_list[i].nick + "!" + _ban_list[i].user + "@" + _ban_list[i].host + " " + _ban_list[i].operator_name + " " + SSTR(_ban_list[i].time));
		for (size_t i = 0; i < banlist.size(); i++)
			client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_BANLIST, _recipients[0] + " " + banlist[i]),client));
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_ENDOFBANLIST, _recipients[0] + " " + RPL_ENDOFBANLIST_MESS),client));
	}
	else if (server._channels[_recipients[0]].users[client.get_nickname()].second.count('o') || client._priveleges.count('O'))
	{
		std::vector<std::string> mask = banparse(_arguments[2]);
		if (_arguments[1] == "+b" || _arguments[1] == "b")
		{
			_ban_list.push_back((Channel::BanMask){mask[0],mask[1],mask[2],client.get_nickname(),time(NULL)});
		}
		else if (_arguments[1] == "-b")
		{
			size_t i = 0;
			while (i < _ban_list.size())
			{
				if ((_ban_list[i].nick == mask[0] || mask[0] == "*") && 
					(_ban_list[i].user == mask[1] || mask[1] == "*") && 
					(_ban_list[i].host == mask[2] || mask[2] == "*"))
					_ban_list.erase(_ban_list.begin() + i);
				else
					i++;
			}
		}
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator 
								it = server._channels[_recipients[0]].users.begin(); 
								it != server._channels[_recipients[0]].users.end(); it++)
				(*it).second.first->_received_msgs.push(notification(client, this));
	}
	else
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MESS),client));
	return (false);
}

std::vector<std::string> Mode::modesParse(std::string modes)
{
	char sign;
	std::vector<std::string> out;
	for (size_t i = 0; i < modes.size(); i++)
	{
		while (modes[i] == '+' || modes[i] == '-')
			sign = modes[i++];
		out.push_back((char[2]){sign,modes[i++]});
	}
	return (out);
}


bool Mode::execute(Server & server, Client & client)
{
	OperatorsCommand::execute(server, client);
	if (_arguments.size() >= 3 && _recipients_types[0] == channel && ((_arguments[1][0] == '+' ||_arguments[1][0] == '-')) &&
		!(server._channels[_recipients[0]].users[client.get_nickname()].second.count('o') || client._priveleges.count('O')))
			client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MESS),client));
	else if (_arguments.size() == 1)
	{
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_CHANNELMODEIS, _recipients[0] + " +"),client));
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_CREATIONTIME, _recipients[0] + " " + SSTR(server._channels[_recipients[0]].creation_time)),client));
	}
	else if (client._channels.count(_recipients[0]) && client._channels[_recipients[0]])
	{
		std::vector<std::string> modes = modesParse(_arguments[1]);
		for (size_t i = 0; i < modes.size(); i++)
		{
			_arguments[1] = modes[i];
			if (_arguments[1] == "b" || (_arguments[1] == "+b") || (_arguments[1] == "-b")) 
				banCase(server,client);
			else if (_arguments.size() == 3 && server._users.count(_arguments[2]))
			{
				if ((_arguments[1] == "+o" || _arguments[1] == "-o") && (client._priveleges.count('O') || server._channels[_arguments[0]].users[client.get_nickname()].second.count('o')))
				{
					if (_arguments[1] == "+o" && (_arguments[2] != client.get_nickname() || client._priveleges.count('O')))
						server._channels[_arguments[0]].users[_arguments[2]].second.insert('o');
					else if (_arguments[1] == "-o" && (_arguments[2] == client.get_nickname() || client._priveleges.count('O')))
						server._channels[_arguments[0]].users[_arguments[2]].second.erase('o');
					for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator 
									it = server._channels[_recipients[0]].users.begin(); 
									it != server._channels[_recipients[0]].users.end(); it++)
					(*it).second.first->_received_msgs.push(notification(client, this));
				}
				else
					client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MESS),client));
			}
			else
				client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHNICK,ERR_NOSUCHNICK_MESS),client));
		}
	}
	else
	{
		throw WrongChannelName();
	}
	std::cout << "Mode works!" << std::endl;

	return false;
}

// std::string Mode::getCommandName() 
// {
// 	return ("MODE");
// }