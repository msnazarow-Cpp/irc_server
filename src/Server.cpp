#include <fcntl.h>
#include "Server.h"
#include "Request.h"
#include "Client.h"

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
    SharedPtr<Client> new_client(new Client(connection, clientAddr));
    _new_users.push_back(new_client);
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
    std::list<SharedPtr<Client> >::iterator it;
    std::map<std::string, SharedPtr<Client> >::iterator it_a;

    bool acted = false;

    for (it = _new_users.begin(); it != _new_users.end(); it++) {
        (*it)->receive(FD_ISSET((*it)->getFd(), &_readFds));
    }
    for (it_a = _full_users.begin(); it_a != _full_users.end(); it++) {
        SharedPtr<Client> client = (*it_a).second;
        client->receive(FD_ISSET(client->getFd(), &_readFds));
    }
    for (it = _new_users.begin(); it != _new_users.end(); it++) {
        SharedPtr<Client> client = (*it_a).second;
        std::queue<Command> commands = client->getReceivedCommands();
        while(!commands.empty()){
            commands.back().exec(this, _new_users[i]);
            commands.pop();
        }
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

const std::vector<SharedPtr<Client> > &Server::getClients() const {
    return _new_users;
}