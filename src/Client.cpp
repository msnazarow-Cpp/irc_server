#include "Client.h"
#include <iostream>
#include <response.h>
#include <stdexcept>
#include <sys/time.h>
#include "Server.h"
#include "Message.h"
#include <unistd.h>

#define BUFFER_SIZE 10000

bool Client::response() {
    this->Combine_messages();
    raw_send(); //TODO: if possible
    return true;
}

int Client::getFd() const {
    return _fd;
}

bool Client::receive(bool fd_is_set) {
    if (!fd_is_set)
        return false;
    //int ret = 1;
    char buffer[BUFFER_SIZE + 1];
    size_t read_ret = read(getFd(), buffer, BUFFER_SIZE);
    buffer[read_ret] = '\0';
    _raw_data += buffer;
    if (_raw_data.empty())
        return false;

    bool save_last = _raw_data.back() != '\n';
    std::vector<std::string> splitted = ft::split(_raw_data, '\n');
    if (save_last) {
        _raw_data.assign(splitted.back());
        splitted.erase(std::prev(splitted.end()));
    } else
        _raw_data.clear();
    for (size_t i = 0; i < splitted.size(); i++) {
        try {
            if (!splitted[i].empty()) //TODO: split problem... kostil
                _received_commands.push(Command(splitted[i], _nick));
        }
        catch (std::exception &e) {
            //TODO:_received_msgs.push("ТЫ ОШИБСЯ");
        }
    }

    return true;
}

Client::~Client() {
    close(_fd);
}

Client::Client(int fd) : _nick(), _raw_data(), _raw_send(), _fd(fd) {
}


void Client::raw_send() {
    static const size_t MAX_CHUNK_SIZE = pow(2, 20);
    if (!_raw_send.empty()) {
        ssize_t chunk_size = std::min(_raw_send.size(), MAX_CHUNK_SIZE);
        ssize_t sended = write(_fd, _raw_send.c_str(), chunk_size);
        //TODO: if (ret <= 0) {
        //TODO:     _status = CLOSE_CONNECTION;
        _raw_send.erase(0, sended);
    }
}

bool Client::hasCommands() const{
    return !_received_commands.empty();
}
Command Client::getCommand()  {
    Command command = _received_commands.back();
    _received_commands.pop();
    return command;
}

void Client::addMsg(const Message &msg) {
    _received_msgs.push(msg);
}

void Client::Combine_messages() {
    while (!_received_msgs.empty()) {
        _raw_send += _received_msgs.back().to_string();
        _received_msgs.pop();
    }
}

const std::string &Client::getNick() const {
    return _nick;
}

void Client::setNick(const std::string &nick) {
    _nick = nick;
}


Command::Command(const std::string &command, const std::string &nick) : client_nick(nick) {
    //TODO: ЗАГЛУШКА!
    std::vector<std::string> splitted = ft::split(command, ' ');
    dst = splitted[0];
    msg = splitted[1];
}

void Command::exec(Server *server) {
    //TODO: ЗАГЛУШКА!
    try {
        Message new_msg(client_nick, msg);
        server->_full_users.at(dst)->addMsg(new_msg);
        //AT ВАЖЕН!!!!
   }
    catch (...) {
        std::cerr << "Catch error ..." << std::endl;
    }
}
