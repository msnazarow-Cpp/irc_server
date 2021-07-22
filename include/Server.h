#pragma once

#include "Client.h"
#include "SharedPtr.h"
#include <stdexcept>
#include <cstring>
#include <set>
#include <list>
#include <Channel.h>
#include <netinet/in.h>
#include "Command.hpp"
typedef int fd_type;

class Server {
private:
	typedef std::map<std::string, SharedPtr<Client> > Clients_map;
	Server();
	Server(const Server &);
	void operator=(const Server &);

	//std::vector<ServConfig> _servers;

	std::list<SharedPtr<Client> > _new_users;
	std::queue<Clients_map::iterator> _to_delete;
    Clients_map _users;
    std::map<std::string, Channel> _channels;
    // TODO: std::map<std::string, Channel> _channels;
	fd_set _readFds;
	fd_set _writeFds;
    size_t _number_of_uneregistered_clients;
	fd_type _socket_fd;
	int _port;
	std::string _host_ip;
	sockaddr_in _sockaddr;
    std::string _password;
 public:
    friend class Command;
	// friend bool Command::execute(Server &server, Client &client);  Не робит почему то
	friend class Invite;
	friend class Join;
	friend class Kick;
	friend class Kill;
	friend class Mode;
	friend class Nick;
	friend class Oper;
	friend class Part;
	friend class Pass;
	friend class Privmsg;
	friend class Quit;
	friend class User;

	Server(int port, const std::string& host_ip);
	Server(int port, const std::string &host_ip, std::string password);
	void initSocket();
	void checkClients();
	void checkSockets();
	int Select();
	int getMaxSockFd() const;
	void newClient();

	class Error : public std::runtime_error {
	 private:
		Error();
	 public:
		explicit Error(const std::string &msg) :
		std::runtime_error("Error: " + msg + ": " + strerror(errno)) {};
	};
	const std::string & getPassword() const;
    void authentificate(Client & client);
    
    std::string hostIp() const;
	void reloadFdSets();
	const std::map<std::string, SharedPtr<Client> > & getClients() const;

};

std::string returnSendableMessageToClient(std::string message, const Client & client);

