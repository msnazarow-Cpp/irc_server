#include "Client.h"
#include <stdexcept>
#include <sys/time.h>
#include "Server.h"
#include "Message.h"
#include <unistd.h>
#include <Parse.hpp>
#include "Command.hpp"
#include <stdint.h>
#include "Parse.hpp"

#define BUFFER_SIZE 10000

Parse Client::parse;

bool Client::response() {
    this->Combine_messages();
    raw_send();
    return true;
}

int Client::getFd() const {
    return _fd;
}

bool Client::receive(bool fd_is_set, Server &server) {
    if (!fd_is_set)
        return false;

    char buffer[BUFFER_SIZE + 1];
    size_t read_ret = read(getFd(), buffer, BUFFER_SIZE);
	if (read_ret == 0)
	{
		server._to_delete.insert(_nickname);
		return true;
	}
	else if (read_ret == SIZE_MAX)
	{
		return true;
	}
	buffer[read_ret] = '\0';
	_raw_data += buffer;
	if (_raw_data.empty())
		return false;
	std::cout << "INPUT : \n" << buffer << std::endl;
    bool save_last = _raw_data[_raw_data.size() - 1] != '\n';
    std::vector<std::string> splitted = ft::split(_raw_data, '\n');
	for (size_t i = 0; i < splitted.size(); i++)
		if (splitted[i][splitted[i].size() - 1] == '\r')
			splitted[i].erase(splitted[i].size() - 1);
	if (save_last) 
	{
		_raw_data.assign(splitted[splitted.size() - 1]);
		splitted.erase(splitted.end() - 1);
	} 
	else
		_raw_data.clear();
    for (size_t i = 0; i < splitted.size(); i++) {
		SharedPtr<Command> comm;
			if (!splitted[i].empty())
			{
				if(splitted[i].substr(0, 6) == "CAP LS")
					_received_msgs.push(":" + server.hostIp() +  " CAP * LS :\r\n");
					// _received_msgs.push(":" + server.hostIp() +  " CAP * LS :multi-prefix\r\n");
				else if (splitted[i].substr(0,4) == "PING" || splitted[i].substr(0,4) == "PONG")
					_received_msgs.push(":" + server.hostIp() + " PONG " + server.hostIp() + " :" + _nickname + "\r\n");
				else if (splitted[i].substr(0,21)  == "CAP REQ :multi-prefix")
					_received_msgs.push(":" + server.hostIp() +  " CAP * NAK multi-prefix\r\n");
				else if(splitted[i].substr(0,7) == "CAP END")
					;
				else
				{
					size_t pos = splitted[i].find_first_not_of(' ');
					if (pos == std::string::npos)
					{	
						if (touch_check)
							_received_msgs.push(clientReply(server.hostIp(), Message(ERR_UNKNOWNCOMMAND, " :"),*this));
						return false;
					}
					std::string firstcommand = splitted[i].substr(pos,splitted[i].size() - pos);
					try
					{
						comm = SharedPtr<Command>(parse.make_command(splitted[i], this));
                 		_received_commands.push(comm);
					}
					catch (const Parse::UknownCommand&)
					{	
						if (touch_check)
							_received_msgs.push(clientReply(server.hostIp(), Message(ERR_UNKNOWNCOMMAND, firstcommand.substr(0,splitted[i].find(' ')) + " :"),*this));
					}
					catch (const Parse::ThoManyArgs&)
					{	
						if (touch_check)
							_received_msgs.push(clientReply(server.hostIp(), Message(ERR_NEEDMOREPARAMS,firstcommand.substr(0,splitted[i].find(' ')) + " :Two many arguments"),*this));
					}
					catch (const Command::WrongArgumentsNumber&)
					{	
						if (touch_check)
							_received_msgs.push(clientReply(server.hostIp(), Message(ERR_NEEDMOREPARAMS, firstcommand.substr(0,splitted[i].find(' ')) + " :Need more arguments"),*this));
					}
					catch (const Command::WrongChannelName&)
					{	
						if (touch_check)
							_received_msgs.push(clientReply(server.hostIp(), Message(ERR_NOSUCHCHANNEL, firstcommand.substr(0,splitted[i].find(' ')) + ":"/* +  ERR_NOSUCHCHANNEL_MESS */),*this));
					}
					catch (const Command::ErrNickname&)
					{	
						if (touch_check)
							_received_msgs.push(clientReply(server.hostIp(), Message(ERR_ERRONEUSNICKNAME, /* firstcommand.substr(0,splitted[i].find(' ')) + */ ":"/* +  ERR_ERRONEUSNICKNAME_MESS */),*this));
					}
					catch (Command::NothingToDo)
					{
						std::cout << "This is ok" <<std::endl;
					}
					
				}
			}
    }

    return true;
}

Client::~Client() {
    close(_fd);
}

Client::Client(int fd) : _nickname(), _raw_data(), _raw_send(), _fd(fd), pass_check(0),nick_check(0),user_check(0),reg_check(0),touch_check(0) {

}

Client::Client(int fd, std::string host): _hostname(host), _nickname(), _raw_data(), _raw_send(), _fd(fd), pass_check(0),nick_check(0),user_check(0),reg_check(0),touch_check(0) 
{
	
}


void Client::raw_send() {
    static const size_t MAX_CHUNK_SIZE = 1048576;
    if (!_raw_send.empty()) 
	{
		ssize_t chunk_size = std::min(_raw_send.size(), MAX_CHUNK_SIZE);
		ssize_t sended = write(_fd, _raw_send.c_str(), chunk_size);
		std::cout << "OUTPUT:\n" << _raw_send << std::endl;
		_raw_send.erase(0, sended);
	}
}

bool Client::hasCommands() const{
    return !_received_commands.empty();
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
        _raw_send += _received_msgs.front();
        _received_msgs.pop();
    }
}


void Client::set_realname(const std::string& realname)
{
	this->_realname = realname;
}

const std::string & Client::get_realname() const
{
	return this->_realname;
}

const std::string & Client::get_nickname() const
{
	return this->_nickname;
}

void Client::set_nickname(const std::string& nickname)
{
	this->_nickname = nickname;
}

const std::string & Client::get_username() const
{
	return this->_username;
}

void Client::set_username(const std::string& username)
{
	this->_username = username;
}

const std::string & Client::get_hostname() const
{
	return this->_hostname;
}

void Client::set_hostname(const std::string& hostname) {
	_hostname = hostname;
}

const std::string & Client::hostIp() const { return _hostIp; }


Client::Client(): _fd(-1)
{
	
}

bool Client::send_waiting() {
    return !_raw_send.empty() || !_received_msgs.empty();
}

std::string notification(const Message & message, const Client & client)
    {
		return (":" + client.get_nickname() + "!" + client.get_username() + "@" + client.get_hostname() + " " + message.message() + "\r\n");
	}

std::string notification(const Client & client, const Command * command)
    {
		return (":" + client.get_nickname() + "!" + client.get_username() + "@" + client.get_hostname() + " " + command->fullCommand() + "\r\n");
	}
	
std::string clientReply(const std::string & hostIp, const Message & message, const Client & client) 
	{
	//	:irc.example.net "254" misha 1 :channels formed

		return (":" + hostIp + " " + message.code() + " " + client.get_nickname() + " " + message.message() + "\r\n");
	}