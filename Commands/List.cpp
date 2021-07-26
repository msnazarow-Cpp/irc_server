#include "List.hpp"
#include "Client.h"
#include "Server.h"
List::List()
{
}

List::~List()
{
}

List::List(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "List", arguments)
{

}

List *List::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new List(full_command, arguments);
}

bool List::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_LISTSTART, RPL_LISTSTART_MESS),client));
	for (std::map<std::string, Channel>::iterator it = server._channels.begin(); it != server._channels.end(); it++)
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_LIST, (*it).first + " " + ft::to_string((*it).second.users.size()) + " :" + (*it).second.getTopic()),client));
	client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_LISTEND, RPL_LISTEND_MESS),client));
	std::cout << "List works!" << std::endl;
	return true;
}

// std::string List::getCommandName() 
// {
// 	return ("List");
// }