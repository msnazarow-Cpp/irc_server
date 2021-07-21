#include <fcntl.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#ifndef SO_NOSIGPIPE
    #define SO_NOSIGPIPE 2 
#endif // !SO_NOSIGPIPE
Server::Server(int port, const std::string &host_ip) : _port(port), _host_ip(host_ip), _sockaddr() {
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
                            (socklen_t *) &addrlen); //TODO: clientAddr and Addrlen?!
    if (connection == -1)
        throw Error("connection");
    SharedPtr<Client> new_client(new Client(connection));
    //TODO:: costil
    rand();
    std::string name = std::to_string(rand() % 1000);
    new_client->setNick(name);
    std::cerr << "New user: " << name << std::endl;
    _full_users[name] = new_client;
    //TODO: costil end
    fcntl(connection, F_SETFL, O_NONBLOCK);
}

int Server::getMaxSockFd() const {
    int maxFd = _socket_fd;
    std::map<std::string, SharedPtr<Client> >::const_iterator client;
    for (client = getClients().cbegin(); client != getClients().cend(); client++) {
        maxFd = std::max((*client).second->getFd(), maxFd);
    }
    std::list<SharedPtr<Client> >::const_iterator new_client;
    for (new_client = _new_users.cbegin(); new_client != _new_users.cend(); new_client++) {
        maxFd = std::max((*new_client)->getFd(), maxFd);
    }
    if (maxFd == -1)
        throw Error("get Max Fd");
    return (maxFd);
}

void Server::reloadFdSets() {
    FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
    std::map<std::string, SharedPtr<Client> >::const_iterator client;
    for (client = getClients().cbegin(); client != getClients().cend(); client++) {
        FD_SET((*client).second->getFd(), &_readFds);
        FD_SET((*client).second->getFd(), &_writeFds);
    }

    std::list<SharedPtr<Client> >::const_iterator new_client;
    for (new_client = _new_users.cbegin(); new_client != _new_users.cend(); new_client++) {
        FD_SET((*new_client)->getFd(), &_readFds);
        FD_SET((*new_client)->getFd(), &_writeFds);
    }
    FD_SET(_socket_fd, &_readFds);
}

void Server::checkClients() {
    typedef std::list<SharedPtr<Client> >::iterator list_iter;
    typedef std::map<std::string, SharedPtr<Client> >::iterator map_iter;
    //TODO:: Vid pipez

    //bool acted = false;

    for (list_iter it = _new_users.begin(); it != _new_users.end(); it++) {
        (*it)->receive(FD_ISSET((*it)->getFd(), &_readFds));
    }

    for (map_iter it_a = _full_users.begin(); it_a != _full_users.end(); it_a++) {
        SharedPtr<Client> client = (*it_a).second;
        client->receive(FD_ISSET(client->getFd(), &_readFds));
    }

    for (list_iter it = _new_users.begin(); it != _new_users.end(); it++) {
        SharedPtr<Client> client = (*it);
        while (client->hasCommands()) {
            client->getCommand().exec(this);
        }
    }

    for (map_iter  it_a = _full_users.begin(); it_a != _full_users.end(); it_a++) {
        SharedPtr<Client> client = (*it_a).second;
        while (client->hasCommands()) {
            client->getCommand().exec(this);
        }
    }

    for (list_iter  it = _new_users.begin(); it != _new_users.end(); it++) {
        if (FD_ISSET((*it)->getFd(), &_writeFds))
            (*it)->response();
    }

    for (map_iter it_a = _full_users.begin(); it_a != _full_users.end(); it_a++) {
        if (FD_ISSET((*it_a).second->getFd(), &_writeFds))
            (*it_a).second->response();
    }
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
    return _full_users;
}