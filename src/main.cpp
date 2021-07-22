#include "Server.h"

volatile bool loop = true;

int main(int ac, char **av)
{
	if (ac != 4) {
		std::cerr << "\033[1;31mTwo argument only!\033[0m" << std::endl;
		return 1;
	}
	std::cout << std::endl << "\033[1;31m" << "WELCOME TO KINGINX" << "\033[0m" << std::endl << std::endl;

	try {
		Server server(atoi(av[1]), av[2], av[3]);
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
