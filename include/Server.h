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
#include <errno.h>
typedef int fd_type;

class Server {
public:
	typedef std::map<std::string, SharedPtr<Client> > Clients_map;
private:
	Server();
	Server(const Server &);
	void operator=(const Server &);
	std::set<std::string> _to_delete;
	std::vector<std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator> _to_delete_from_channels;
    Clients_map _users;
    std::map<std::string, Channel> _channels;
    fd_set _readFds;
	fd_set _writeFds;
    size_t _number_of_uneregistered_clients;
	fd_type _socket_fd;
	fd_type _max_fd;
	int _port;
	std::string _host_ip;
	sockaddr_in _sockaddr;
    std::string _password;
 public:
    friend class Command;
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
	friend class Who;
	friend class List;
	friend class Notice;
	friend class Client;
	friend class Ison;
	friend class Whois;
	friend class Topic;
	friend class Names;
	friend class Userhost;
	Server(int port, const std::string& host_ip);
	Server(int port, const std::string &host_ip, std::string password);

	void initSocket();
	void checkClients();
	void checkSockets();
	int Select();
	int getMaxSockFd() const;
	void newClient();
	void update_fd_set(fd_type fd, fd_set *set);;

	class Error : public std::runtime_error {
	 private:
		Error();
	 public:
		explicit Error(const std::string &msg) :
		std::runtime_error("Error: " + msg + ": " + strerror(errno)) {};
	};
	const std::string & getPassword() const;
    std::string hostIp() const;
	void reloadFdSets();
	const std::map<std::string, SharedPtr<Client> > & getClients() const;

};
