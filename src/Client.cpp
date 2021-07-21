#include "Client.h"
#include <iostream>
#include <response.h>
#include <stdexcept>
#include <sys/time.h>
#include "response_generator.h"

#define BUFFER_SIZE 10000

bool Client::response() {
    if (_status != READY_TO_SEND && _status != SENDING)
        return false;
    if (_status == SENDING) {
        this->raw_send();
        return true;
    }
    //Response rsp = get_response(_req, serv_);
    //_raw_msg = rsp.toString();
    _status = SENDING;
    next_status = _req.isComplete() ? READY_TO_READ : CLOSE_CONNECTION;
    _req.clear();
    return true;
}

int Client::getFd() const {
    return _fd;
}

bool Client::receive(bool fd_is_set) {
    if (!fd_is_set)
        return false;
    int ret = 1;
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
    }
    for (size_t i = 0; splitted.size(); i++) {
        try {
            _received_commands.push(Command(splitted[i]));
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

Client::Client(int fd)
        : _fd(fd){
}


void Client::raw_send() {
    static const size_t MAX_CHUNK_SIZE = pow(2, 20);
    if (_sended < _raw_msg.size()) {
        ssize_t chunk_size = std::min(_raw_msg.size() - _sended, MAX_CHUNK_SIZE);
        ssize_t ret = send(_fd, &(_raw_msg.c_str()[_sended]), chunk_size, 0);
        if (ret <= 0) {
            _status = CLOSE_CONNECTION;
        } else {
            _sended += ret;
        }
    }
    if (_sended == _raw_msg.size()) {
        _sended = 0;
        _status = next_status;
    }
}

e_client_status Client::GetStatus() {
    return _status;
}

const std::queue<Command> &Client::getReceivedCommands() const {
    return _received_commands;
}


Command::Command(std::basic_string<char> basicString) {

}
