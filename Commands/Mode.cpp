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
	_recipient = arguments[0];
	if (_recipient[0] == '#')
		_recipient_type = channel;
	else
		_recipient_type = user;
}

Mode *Mode::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Mode(full_command, arguments);
}

bool Mode::execute(Server & server, Client & client)
{
	OperatorsCommand::execute(server, client);
	if (_arguments.size() == 1)
	{
		client._received_msgs.push(clientReply(Message(RPL_CHANNELMODEIS, _recipient + " +"),client));
		client._received_msgs.push(clientReply(Message(RPL_CHANNELMODEIS, _recipient + " " + SSTR(clock())),client));
	}
	else if (_arguments[1] == "b")
	{
		std::vector<std::string> & banlist =  server._channels[_recipient].ban_list;
		for (size_t i = 0; i < banlist.size(); i++)
			client._received_msgs.push(clientReply(Message(RPL_BANLIST, _recipient + " " + server._channels[_recipient].ban_list[i]),client)); //to do нужно выводить время бана, а не текущее
		client._received_msgs.push(clientReply(Message(RPL_ENDOFBANLIST, _recipient + " " + RPL_ENDOFBANLIST_MESS),client));
	}
	else if (_arguments[1] == "+b")
	{
		_full_command += "!*@*";
		server._channels[_recipient].ban_list.push_back(_full_command + " " + client.get_nickname() + " " + SSTR(clock()));
		for (std::map<std::string, std::pair<Client *, std::set<char> > >::iterator it = server._channels[_recipient].users.begin(); 
		it != server._channels[_recipient].users.begin(); it++)
			(*it).second.first->_received_msgs.push(notification(client, this));
	}
	std::cout << "Mode works!" << std::endl;
	return false;
}

// std::string Mode::getCommandName() 
// {
// 	return ("MODE");
// }