#include "User.hpp"
#include "Client.h"
#include "Server.h"
#include "Message.h"

User::User()
{
}

User::~User()
{
}

User::User(const std::string & full_command, const std::vector<std::string> & arguments): Command(full_command, "USER", arguments)
{
	if (arguments.size() != 4)
		throw WrongArgumentsNumber();
	_username = arguments[0];
	// _hostname = arguments[1];
	// _servername = arguments[2];
	_realname = arguments[3];
	// size_t i = 4;
	// while (i < arguments.size())
	// 	_realname += arguments[i++];
}

User *User::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new User(full_command, arguments);
}

bool User::execute(Server & server, Client & client)
{
	client.touch_check = true;
	if (client.user_check)
	{	
		client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_ALREADYREGISTRED, ":"), client));
		return false;
	}
	client.user_check = true;
	client.set_realname(_realname);
	client.set_username(_username);
	// client.set_hostname(_hostname);
	if (client.nick_check && client.user_check){
		if (client.pass_check)
			{
				client._received_msgs.push(clientReply(server.hostIp(), Message("001", ":Welcome abroad!"),client));
				client._received_msgs.push(clientReply(server.hostIp(), Message("376", ":Welcome abroad!"),client));
				
				client.reg_check = true;
			}
		else
			{
				client._received_msgs.push("ERROR :Access denied: Bad password?\r\n");
				//close(client.getFd()); // ТаК??
				server._to_delete.push_back(server._users.find(client.get_nickname()));
			}
	}
	return false;
}

// std::string User::getCommandName() 
// {
// 	return ("USER");
// }