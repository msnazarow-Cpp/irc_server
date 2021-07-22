#pragma once

#include "Message.h"
#include <sys/time.h>
#include <cmath>
#include <queue>
#include "SharedPtr.h"
#include "Message.h"
class Parse;
class Command;
class Server;
class Client;

// class Command{
// public:
//     Command(const std::string& basicString, const std::string&);
//     std::string msg;
//     std::string dst;
//     std::string client_nick;
//     void exec(Server*);
// };//TODO sgertrud
enum Status
	{
		unregistered,
		pass_passing,
		nick_having,
		registered_user
	};
class Client {

private:
	std::string _nickname;
	std::string _username;
	std::string _hostname;
	std::string _realname;
	std::string _raw_data;
    std::string _raw_send;
	std::string _hostIp;
    const int _fd;
	static Parse parse;
    Status    _status;

public:
    Client(int fd);
    Client(int fd, std::string host);
    ~Client();
	;

   //NEW
    std::queue<std::string> _received_msgs;
    std::queue<SharedPtr<Command> > _received_commands;
    bool receive(bool);
    bool response();
    void raw_send();
    bool send_waiting()
	{
		return !_raw_send.empty();
	}
    //e_client_status GetStatus();
    int getFd() const;
    void Combine_messages();
    void addMsg(const std::string &msg);

    SharedPtr<Command> popCommand();
    bool hasCommands() const;

    Status status() const;
    void setStatus(Status status);
	std::string get_nickname() const;
	void set_nickname(const std::string& nickname);
	std::string get_username() const; 
	void set_username(const std::string& username);
	std::string get_hostname() const;
	void set_hostname(const std::string& hostname);
	std::string get_realname() const;
	void set_realname(const std::string& realname);

	std::string hostIp() const;
};
