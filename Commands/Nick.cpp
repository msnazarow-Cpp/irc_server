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
}

Nick *Nick::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Nick(full_command, arguments);
}

bool Nick::execute(Server & server, Client & client)
{
	client.touch_check = true;
	if (server.getClients().count(_newnick) == 0)
	{
		client.nick_check = true;
		 //TO do отправляется многократно если клиенты состоят в нескольких каналах
		if (client.reg_check)
		{
			client._received_msgs.push(notification(client, this));
			for (std::map<std::string, Channel *>::iterator it = client._channels.begin(); it != client._channels.end(); it++)
			{
				for (std::map<std::string, std::pair<Client *, std::set<char> > >::iterator it = server._channels[(*it).first].users.begin(); it != server._channels[(*it).first].users.end(); it++)
				{
					if ((*it).first != client.get_nickname())
						server._users[(*it).first]->_received_msgs.push(notification(client, this));
				}
			}
		}
		server._users[_newnick] = server._users[client.get_nickname()];
		server._to_delete.push(server._users.find(client.get_nickname()));
		client.set_nickname(_newnick);
		if (!client.reg_check && client.nick_check && client.user_check)
		{
			if (client.pass_check)
				{
					client._received_msgs.push(clientReply(Message("001", ":Welcome abroad!"),client));
					client.reg_check = true;
				}
			else
				client._received_msgs.push("ERROR :Access denied: Bad password?\r\n");
		}
	}
	else
		client._received_msgs.push(clientReply(Message(ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MESS),client));
	std::cout << "Nick works!" << std::endl;
	return true;
}

// std::string Nick::getCommandName() 
// {
// 	return ("NICK");
// }