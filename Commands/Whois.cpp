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

std::string Whois::person(Client & client)
{
	return (client.get_nickname() + " ~" + client.get_username() + " " + client.get_hostname() + "* :" + client.get_realname());
}
std::string Whois::channels(Client & client)
{
	std::string out = client.get_nickname() + " :";
	for (std::map<std::string, Channel *>::iterator it = client._channels.begin(); it != client._channels.end(); it++)
	{
		if ((*it).second->users[client.get_nickname()].second.count('o'))
			out += "@";
		out += (*it).first + " ";
	}
	return out;
}

bool Whois::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);;
	//client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOisREPLY, RPL_WHOisSTART_MESS),client));
		// #define RPL_WHOISUSER				"311"		// "<nick> <user> <host>*  :<real name>"
		// #define RPL_WHOISSERVER				"312"		// "<nick> <server> :<server info>"
		// #define RPL_WHOISOPERATOR			"313"		// "<nick> :is an IRC operator"
		// #define RPL_WHOISOPERATOR_MESS		":is an IRC operator"
		// #define RPL_WHOISIDLE				"317"		// "<nick> <integer> :seconds idle"
		// #define RPL_ENDOFWHOIS				"318"		// "<nick> :End of /WHOIS list"
		// #define RPL_ENDOFWHOIS_MESS			":End of WHOIS list"
	if (server._users.count(_arguments[0]))
	{
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOISUSER, person(*server._users[_arguments[0]])),client));
		client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_WHOISCHANNELS, channels(*server._users[_arguments[0]])),client));

	}
	client._received_msgs.push(clientReply(server.hostIp(), Message(RPL_ENDOFWHOIS, RPL_ENDOFWHOIS_MESS),client));
	std::cout << "Whois works!" << std::endl;
	return true;
}

// std::string Whois::getCommandName() 
// {
// 	return ("Whois");
// }