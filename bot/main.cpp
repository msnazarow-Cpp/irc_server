#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include "utils.h"

std::string connect_msg(const std::string& bot_name, const std::string& password){
	return "PASS " + password + "\r\n" + "NICK " + bot_name + "\r\nUSER " + bot_name + " * * *\r\n";
}

char buff[1024];

void exit(int i);
//execute ./irc_echo_bot port ip bot_name password
int main(int argc, char** argv)
{
	int sock;
	struct sockaddr_in addr;
	std::vector<std::string> args(argv, argv + argc);
	if (args.size() != 5)
	{
		std::cout << "./irc_echo_bot port ip bot_name password" << std::endl;
		return 0;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(args[1].c_str()));
	addr.sin_addr.s_addr = 0; //TODO: change to custom ip addr
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(2);
	}

	std::string message = connect_msg(args[3], args[4]);
	std::cerr << message <<std::endl << "size: " << message.size() << std::endl;
	int sended = send(sock, message.c_str(), message.size(), 0);
	std::cerr << "Sended" << sended << std::endl;
	while (1)
	{
		int rec = recv(sock, buff, 1024, 0);
		buff[rec] = 0;
		printf(buff);
		std::string raw = buff;
		if(raw.find("PRIVMSG") == std::string::npos)
			continue;
		std::vector<std::string> splitted = ft::split(buff, ':');
		std::cerr <<"s_size:" << splitted.size() <<std::endl;
		std::string msg = "PRIVMSG " + ft::split(splitted[0], '!')[0] + " :U sad:" + splitted[1];
		int sended = send(sock, msg.c_str(), msg.size(), 0);
		for(auto it:splitted)
			std::cerr << it << std::endl;
		std::cerr << std::endl;
		sleep(1);
	}
	close(sock);

	return 0;
}

