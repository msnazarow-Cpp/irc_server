#include "Whois.hpp"
#include "Client.h"
#include "Server.h"
Whois::Whois()
{
}

Whois::~Whois()
{
}

Whois::Whois(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "Whois", arguments)
{

}

Whois *Whois::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Whois(full_command, arguments);
}

std::string Whois::response(std::map<std::string, Channel>::iterator it, Server & server, Client & client)
{
	return (client.get_username() + " " + client.get_hostname() + " " + server.hostIp() + " " + client.get_nickname() + " :" + client.get_realname());
}
bool Whois::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	//client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOisREPLY, RPL_WHOisSTART_MESS),client));
	for (std::map<std::string, Channel>::iterator it = server._channels.begin(); it != server._channels.end(); it++)
		for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it_u = (*it).second.users.begin(); it_u != (*it).second.users.end(); it_u++)
			client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOisREPLY, response(it, server, *(*it_u).second.first)),client));
	client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_ENDOFWHOis, RPL_ENDOFWHOis_MESS),client));
	std::cout << "Whois works!" << std::endl;
	return true;
}

// std::string Whois::getCommandName() 
// {
// 	return ("Whois");
// }