#include <fcntl.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include "Command.hpp"
#include "Privmsg.hpp"
#include <algorithm>
#include <memory>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef SO_NOSIGPIPE
    #define SO_NOSIGPIPE 2 
#endif // !SO_NOSIGPIPE

Server::Server(int port, const std::string &host_ip) : _port(port), _host_ip(host_ip), _sockaddr() {
    bzero(&_sockaddr, sizeof(sockaddr_in));
    FD_ZERO(&_writeFds);
    FD_ZERO(&_readFds);
    initSocket();
}
Server::Server(int port, const std::string &host_ip, std::string password) : _port(port), _host_ip(host_ip) {
	_number_of_uneregistered_clients = 0;
	_password = password;
	bzero(&_sockaddr, sizeof(sockaddr_in));
	FD_ZERO(&_writeFds);
	FD_ZERO(&_readFds);
	initSocket();
}
void Server::initSocket() {
    _sockaddr.sin_family = AF_INET; // ipV4
    _sockaddr.sin_port = htons(_port);
    _sockaddr.sin_addr.s_addr = 0; //TODO host_port

    this->_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket_fd == -1)
        throw Error("create socket");
    int opt = 1;
    if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        throw Error("setsockopt");
    if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof(opt)) == -1)
        throw Error("setsockopt");
    if (bind(this->_socket_fd, (struct sockaddr *) &_sockaddr, sizeof(sockaddr))
        == -1)
        throw Error("bind, maybe port busy");
    if (listen(this->_socket_fd, -1) < 0)
        throw Error("listen on socket");
}

void Server::newClient() {
    sockaddr_in clientAddr;
    int addrlen = sizeof(sockaddr);

    int connection = accept(this->_socket_fd,
                            (struct sockaddr *) &clientAddr,
                            (socklen_t *) &addrlen);
							
    if (connection == -1)
        throw Error("connection");
	 SharedPtr<Client> new_client(new Client(connection, _host_ip));
	
	if (_password.empty())
		new_client->pass_check = true;
	new_client->set_hostname(inet_ntoa(clientAddr.sin_addr));
    std::string name = "__unregistered__" + ft::to_string(_number_of_uneregistered_clients++);
    new_client->set_nickname(name);
    std::cerr << "New user: " << name << std::endl;
    _users[name] = new_client;
    fcntl(connection, F_SETFL, O_NONBLOCK);
}

const std::string & Server::getPassword() const {
    return _password;
}

void Server::update_fd_set(fd_type fd, fd_set *set) {
    _max_fd = std::max(fd, _max_fd);
    FD_SET(fd, set);
}


int Server::getMaxSockFd() const {
    return (_max_fd);
}

void Server::reloadFdSets() {
	_max_fd = -1;
	FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
	update_fd_set(_socket_fd, &_readFds);
    std::map<std::string, SharedPtr<Client> >::const_iterator client;
    for (client = getClients().begin(); client != getClients().end(); client++) {
    	SharedPtr<Client> p_client = client->second;
    	if(p_client->send_waiting())
			update_fd_set(p_client->getFd(), &_writeFds);
		update_fd_set(p_client->getFd(), &_readFds);
    }
}

void Server::checkClients() {

    typedef std::map<std::string, SharedPtr<Client> >::iterator map_iter;

    for (map_iter it_a = _users.begin(); it_a != _users.end(); it_a++) {
        SharedPtr<Client> client = (*it_a).second;
        client->receive(FD_ISSET(client->getFd(), &_readFds), *this);
    }

    for(map_iter it_a = _users.begin(); it_a != _users.end();it_a++)
	{
        SharedPtr<Client> client = (*it_a).second;
        while (client->hasCommands()) {
			SharedPtr<Command> comm;
            try
            {
                comm = client->popCommand();
                comm->execute(*this,*client);
            }
            catch(Command::WrongChannelName &)
            {
				ERR_NOSUCHCHANNEL;
					client->_received_msgs.push(clientReply(this->hostIp(), Message(ERR_NOSUCHCHANNEL, comm->arguments()[0] + ":"), *client));
            }
        }
    }

    for (map_iter it_a = _users.begin(); it_a != _users.end(); it_a++) {
        if (FD_ISSET((*it_a).second->getFd(), &_writeFds))
            (*it_a).second->response();
    }
		for (std::set<std::string>::iterator it = _to_delete.begin(); it != _to_delete.end();)
		{
			std::set<std::string>::iterator next = ++it;
			it--;
			if (_users[*it]->_received_msgs.empty())
			{	
				_users.erase(*it);
				_to_delete.erase(it); // Tut sega bila? 
			}
			it = next;
		}
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end();)
	{
		std::map<std::string, Channel>::iterator next = ++it;
		it--;
		if ((*it).second.users.empty())
			_channels.erase(it);
		it = next;
	}
}


std::string Server::hostIp() const
	{
		return _host_ip;
	}
int Server::Select() {
    reloadFdSets();
    struct timeval tv = {10, 0};
    return (select(getMaxSockFd() + 1, &_readFds, &_writeFds, NULL, &tv));
}

void Server::checkSockets() {
    if (FD_ISSET(this->_socket_fd, &_readFds))
        this->newClient();
}

const std::map<std::string, SharedPtr<Client> > &Server::getClients() const {
    return _users;
}