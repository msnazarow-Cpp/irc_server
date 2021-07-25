#pragma once

#include "Message.h"
#include <sys/time.h>
#include <cmath>
#include <queue>
#include "SharedPtr.h"
#include "Message.h"
#include <set>
class Parse;
class Command;
class Server;
class Client;
class Channel;
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
	std::string _hostname;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	std::string _raw_data;
    std::string _raw_send;
	std::string _hostIp;
	
	const int _fd;
	static Parse parse;

public:
	std::set<char> _priveleges;
	bool pass_check;
	bool nick_check;
	bool user_check;
	bool reg_check;
	bool touch_check;
	Client();
    Client(int fd);
    Client(int fd, std::string host);
    ~Client();

   //NEW
	std::map <std::string, Channel *> _channels;
	std::queue<std::string> _received_msgs;
	std::queue<SharedPtr<Command> > _received_commands;
	//bool receive(bool);
	bool receive(bool, Server & server);
	bool response();
	void raw_send();
	bool send_waiting()
	{
		return !_raw_send.empty() || !_received_msgs.empty();
	}
    //e_client_status GetStatus();
    int getFd() const;
    void Combine_messages();
    void addMsg(const std::string &msg);

    SharedPtr<Command> popCommand();
    bool hasCommands() const;

	const std::string &get_nickname() const;
	void set_nickname(const std::string& nickname);
	const std::string &get_username() const; 
	void set_username(const std::string& username);
	const std::string &get_hostname() const;
	void set_hostname(const std::string& hostname);
	const std::string &get_realname() const;
	void set_realname(const std::string& realname);

	const std::string & hostIp() const;

	//const std::set<char> & priveleges() const { return _priveleges; }
};

std::string notification(const Message & message, const Client & client);

std::string notification(const Client & client, const Command * command);
std::string clientReply(const std::string & hostIp, const Message & message, const Client & client);
