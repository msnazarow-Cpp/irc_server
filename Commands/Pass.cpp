#include "Pass.hpp"
#include "Server.h"
Pass::Pass()
{
}

Pass::~Pass()
{
}

Pass::Pass(const std::string & full_command, const std::vector<std::string> & arguments): Command(full_command, "PASS", arguments)
{
	if (arguments.size() != 1)
		throw WrongArgumentsNumber();
	_password = arguments[0];
}

Pass *Pass::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Pass(full_command, arguments);
}

bool Pass::execute(Server & server, Client & client)
{
	client.touch_check = true;
	if (client.reg_check) {
        client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MESS), client));
        return (false);
	}
	if (server.getPassword() != _password)
		client.pass_check = false;
	else if (client.pass_check)
		{
			client._received_msgs.push(clientReply(server.hostIp(), Message(ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MESS), client));
			return false;
		}
	else
		client.pass_check = true;
	if (client.nick_check && client.user_check){
	if (client.pass_check)
        {
            client._received_msgs.push(clientReply(server.hostIp(), Message("001", ":Welcome abroad!"),client));
            client._received_msgs.push(clientReply(server.hostIp(), Message("376", ":Feel free!"),client));
            client.reg_check = true;
        }
	else
			client._received_msgs.push("ERROR :Access denied: Bad password?\r\n");
	}
	std::cout << "Pass works!" << std::endl;
	return false;
}