#include "Client.h"
#include <iostream>
#include <response.h>
#include <stdexcept>
#include <sys/time.h>
#include "Server.h"
#include "Message.h"
#include <unistd.h>
#include <Parse.hpp>
#include "Command.hpp"

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
    std::vector<std::string> splitted = ft::split(_raw_data, "\r\n");
    if (save_last) {
        _raw_data.assign(splitted.back());
        splitted.erase(std::prev(splitted.end()));
    } else
        _raw_data.clear();
    for (size_t i = 0; i < splitted.size(); i++) {
		SharedPtr<Command> comm;
        try 
		{
			if (!splitted[i].empty())
			{
				comm = SharedPtr<Command>(Parse::make_command(splitted[i]));             //TODO: split problem... kostil
                _received_commands.push(comm);
			}
        }
		catch(const Parse::CommandNotValidExeption & e)
		{
			_received_msgs.push(returnSendableMessageToClient(e.what(), *this));
		}
		catch(const Command::WrongArgumentsNumber &e)
		{
			_received_msgs.push(returnSendableMessageToClient(splitted[0] + ": " + e.what(), *this));
		}
		catch(const std::exception& e)
		{
			//TODO:_received_msgs.push("ТЫ ОШИБСЯ");
		}
    }

    return true;
}

Client::~Client() {
    close(_fd);
}

Client::Client(int fd) : _nickname(), _raw_data(), _raw_send(), _fd(fd), _status(unregistered) {
}

Client::Client(int fd, std::string host):_fd(fd)
{
	_hostIp = host;	
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

Status Client::status() const
{
    return _status;
}

void Client::setStatus(Status status) 
{
    _status = status;
}
SharedPtr<Command> Client::popCommand()  {
    SharedPtr<Command> command = _received_commands.front();
    _received_commands.pop();
    return command;
}

void Client::addMsg(const std::string &msg) {
    _received_msgs.push(msg);
}

void Client::Combine_messages() {
    while (!_received_msgs.empty()) {
        _raw_send += _received_msgs.front().c_str();
        _received_msgs.pop();
    }
}


void Client::set_realname(std::string _realname)
{
	this->_realname = _realname;
}

std::string Client::get_realname() const
{
	return this->_realname;
}

std::string Client::get_nickname() const
{
	return this->_nickname;
}

void Client::set_nickname(std::string _nickname)
{
	this->_nickname = _nickname;
}

std::string Client::get_username() const
{
	return this->_username;
}

void Client::set_username(std::string _username)
{
	this->_username = _username;
}

std::string Client::get_hostname() const
{
	return this->_hostname;
}

void Client::set_hostname(std::string hostname) {
	_hostname = hostname;
}

std::string Client::hostIp() const { return _hostIp; }


// Command::Command(const std::string &command, const std::string &nick) : client_nick(nick) {
//     //TODO: ЗАГЛУШКА!
//     std::vector<std::string> splitted = ft::split(command, ' ');
//     dst = splitted[0];
//     msg = splitted[1];
// }

// void Command::exec(Server *server) {
//     //TODO: ЗАГЛУШКА!
//     try {
//         Message new_msg(client_nick, msg);
//         server->_users.at(dst)->addMsg(new_msg);
//         //AT ВАЖЕН!!!!
//    }
//     catch (...) {
//         std::cerr << "Catch error ..." << std::endl;
//     }
// }
