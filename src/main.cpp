#include "Server.h"

volatile bool loop = true;

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "\033[1;31mOne argument only!\033[0m" << std::endl;
		return 1;
	}
	std::cout << std::endl << "\033[1;31m" << "WELCOME TO KINGINX" << "\033[0m" << std::endl << std::endl;

	int port = atoi(av[1]); //TODO verifiy
	std::cout << port << std::endl;
    std::string host = ""; //std::string(av[2]); //TODO: (ip)

	try {
		Server server(port, host);
		while (loop)
		{
			int ret = server.Select();
			if ( ret == -1 )
				throw Server::Error("select SUPER MSG");
			if ( ret == 0 ) {
				continue ;
			}
			server.checkSockets();
			server.checkClients();
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
