#pragma once

#include "Client.h"
#include "SharedPtr.h"
#include <stdexcept>
#include <cstring>
#include <set>
#include <list>
#include <Channel.h>
#include <cerrno>
#include <netinet/in.h>

typedef int fd_type;

class Server {
 public:
    friend class Command;
	Server(int port, const std::string& host_ip);

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
 private:
	Server();
	Server(const Server &);
	void operator=(const Server &);

	//std::vector<ServConfig> _servers;

	std::list<SharedPtr<Client> > _new_users;
    std::map<std::string, SharedPtr<Client> > _full_users;
    std::map<std::string, Channel> _channels;
    // TODO: std::map<std::string, Channel> _channels;
	fd_set _readFds;
	fd_set _writeFds;

	fd_type _socket_fd;
	int _port;
	std::string _host_ip;
	sockaddr_in _sockaddr;
	void reloadFdSets();
	const std::map<std::string, SharedPtr<Client> > & getClients() const;
};
