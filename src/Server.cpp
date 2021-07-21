#include <fcntl.h>
#include "Server.h"
#include "Request.h"
#include "Client.h"

Server::Server(int port, const std::string& host_ip): _port(port), _host_ip(host_ip) {
	_sockaddr.sin_family = AF_INET; // ipV4
	_sockaddr.sin_port = htons(_port);
	_sockaddr.sin_addr.s_addr = inet_addr(_host_ip.c_str());
	FD_ZERO(&_writeFds);
	FD_ZERO(&_readFds);
	initSocket();
}

void Server::initSocket() {
		this->_socket_fd = socket(AF_INET, SOCK_STREAM, 0));
		if (this->_socket_fd == -1)
			throw Error("create socket");
		int opt = 1;
		if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR  , &opt, sizeof(opt)) == -1)
			throw Error("setsockopt");
		if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_NOSIGPIPE  , &opt, sizeof(opt)) == -1)
			throw Error("setsockopt");
		if (bind(this->_socket_fd, (struct sockaddr *) &_sockaddr, sizeof(sockaddr))
			== -1)
			throw Error("bind, maybe port busy");
		if (listen(this->_socket_fd, -1) < 0)
			throw Error("listen on socket");
}

void Server::newClient(int indexServer) {
	sockaddr_in clientAddr;
	int addrlen = sizeof(sockaddr);

	int connection = accept(this->_socket_fd,
							(struct sockaddr *) &clientAddr,
							(socklen_t *) &addrlen); //TODO: clientAddr and Addrlen?!
	if (connection == -1)
		throw Error("connection");
	SharedPtr<Client> new_client(new Client(_servers[indexServer], connection, clientAddr));
	_clients.push_back(new_client);
	fcntl(connection, F_SETFL, O_NONBLOCK);
}

int Server::getMaxSockFd() const {
	int maxFd = _socket_fd;
	for (size_t i = 0; i < getClients().size(); ++i)
		maxFd = std::max(getClients()[i]->getFd(), maxFd);

	if (maxFd == -1)
		throw Error("get Max Fd");
	return (maxFd);
}

void Server::reloadFdSets() {
	FD_ZERO(&_readFds);
	FD_ZERO(&_writeFds);
	std::vector<SharedPtr<Client> >::const_iterator client;
	for (client = getClients().cbegin(); client != getClients().cend(); client++) {
		FD_SET((*client)->getFd(), &_readFds);
		FD_SET((*client)->getFd(), &_writeFds);
	}
	FD_SET(_socket_fd, &_readFds);
}

void Server::checkClients() {
	std::vector<SharedPtr<Client> >::iterator it;
	bool acted = false;
	for (it = _clients.begin(); it != _clients.end();) {
		if (FD_ISSET((*it)->getFd(), &_readFds) &&
			(*it)->GetStatus() == READY_TO_READ)
			acted = acted || (*it)->receive();
		else if (FD_ISSET((*it)->getFd(), &_writeFds))
			acted = acted || (*it)->response();

		if(!acted)
		    (*it)->check();

		if ((*it)->GetStatus() == CLOSE_CONNECTION)
			_clients.erase(it);
		else
			++it;
	}
}

int Server::Select() {
	reloadFdSets();
	struct timeval tv = {10, 0};
	return (select(getMaxSockFd() + 1, &_readFds, &_writeFds, NULL, &tv));
}

void Server::checkSockets() {
	int kostil_ubrat ;  //TODO: удалить осталось от множества серверов
		if (FD_ISSET(this->_socket_fd, &_readFds))
			this->newClient(kostil_ubrat);
}

const std::vector<SharedPtr<Client> > &Server::getClients() const {
	return _clients;
}