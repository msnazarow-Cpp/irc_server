#include "Nick.hpp"
#include "Server.h"
#include "Parse.hpp"
Nick::Nick()
{
}

Nick::~Nick()
{
}

Nick::Nick(const std::string & full_command, const std::vector<std::string> & arguments): Command(full_command, "NICK", arguments)
{
	if (arguments.size() < 1)
		throw WrongArgumentsNumber();
	if (arguments.size() > 1)
		throw Parse::ThoManyArgs();
	_newnick = arguments[0];
	if (_newnick == "oper" || _newnick == "admin")
		throw ErrNickname();
	for (size_t i = 0; i < _newnick.length(); i++)
	{
		if (!(isalnum(_newnick[i]) || _newnick[i] == '|' || _newnick[i] == '_'))
			throw ErrNickname();
	}
}

Nick *Nick::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Nick(full_command, arguments);
}

bool Nick::execute(Server & server, Client & client)
{
	// if (_newnick == client.get_nickname())
	// 	client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NICKNAMEINUSE, ":Welcome abroad!"),client));

	client.touch_check = true;
	std::set<SharedPtr<Client> > releted_users;
	releted_users.insert(server._users[client.get_nickname()]);
	if (server.getClients().count(_newnick) == 0)
	{
		client.nick_check = true;
		if (client.reg_check)
		{
			for (std::map<std::string, Channel *>::iterator it_ch = client._channels.begin(); it_ch != client._channels.end(); it_ch++)
			{
				(*it_ch).second->users[_newnick] = (*it_ch).second->users[client.get_nickname()];
				(*it_ch).second->users.erase(client.get_nickname());
				// server._to_delete_from_channels.push_back((*it_ch).second->users.find(client.get_nickname()));
				for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = (*it_ch).second->users.begin(); it != (*it_ch).second->users.end(); it++)
					if ((*it).first != _newnick)
						releted_users.insert(server._users[(*it).first]);
			}
			for (std::set<SharedPtr<Client> >::iterator it = releted_users.begin(); it != releted_users.end(); it++)
				(*it)->_received_msgs.push(notification(client, this));
		}
		server._users[_newnick] = server._users[client.get_nickname()];
		server._to_delete.push_back(server._users.find(client.get_nickname()));
		client.set_nickname(_newnick);
		if (!client.reg_check && client.nick_check && client.user_check)
		{
			if (client.pass_check)
				{
					client._received_msgs.push(clientReply(server.hostIp(), Message("001", ":Welcome abroad!"),client));
					client._received_msgs.push(clientReply(server.hostIp(), Message("376", ":Welcome abroad!"),client));
					client.reg_check = true;
				}
			else
				client._received_msgs.push("ERROR :Access denied: Bad password?\r\n");
		}
	}
	else
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MESS),client));
	std::cout << "Nick works!" << std::endl;
	return true;
}

// std::string Nick::getCommandName() 
// {
// 	return ("NICK");
// }