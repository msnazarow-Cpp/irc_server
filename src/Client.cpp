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
    return fd_;
}

bool Client::receive(bool fd_is_set) {
    if(fd_is_set)
    {
        raw_data += read(1000);
        //read to raw_data;
    }
    //TODO:: list of commands
    //split raw data
    //raw_data = raw_data_splited.back()
    //COMMAND
    if (_status != READY_TO_READ)
        return false;
    try {
        if (_req.receive() <= 0)
            return false;
        if (_req.isComplete()) {
            _status = READY_TO_SEND;
        }
    }
    catch (std::exception &e) {
        _req.clear();
        _status = READY_TO_SEND;
        std::cout << e.what() << std::endl;
    }
    return true;
}

Client::~Client() {
    close(fd_);
}

Client::Client(int fd, const sockaddr_in &clientAddr)
        : fd_(fd), _sended(0), _status(READY_TO_READ), _req(fd), _clientAddr(clientAddr) {
}


void Client::raw_send() {
    static const size_t MAX_CHUNK_SIZE = pow(2, 20);
    if (_sended < _raw_msg.size()) {
        ssize_t chunk_size = std::min(_raw_msg.size() - _sended, MAX_CHUNK_SIZE);
        ssize_t ret = send(fd_, &(_raw_msg.c_str()[_sended]), chunk_size, 0);
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


