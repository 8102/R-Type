# include "Connection.hh"
# include <stdlib.h> // thug life

# define _PROTOCOL_ID 0xff423861

# ifdef _WIN32 

	void my_wait(float seconds)
	{
		Sleep(static_cast<int>(seconds * 1000.0f));
	}

# else

	#include <unistd.h>
	void my_wait(float seconds)
	{
		usleep(static_cast<int>(seconds * 1000000.0f));
	}

# endif

int main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " [address] [port]" << std::endl;
		return (-1);
	}
	Connection::initConnection();
	if (argc == 2)
	{
		// server
		Connection server(_PROTOCOL_ID);
		if (!server.listen(atoi(argv[1])))
			return 1;
		char ret[100] = {0};
		while (true)
		{
			if (server.receivePacket(ret, 99))
			{
				std::cout << ret << std::endl;
				break;
			}
			my_wait(1);
		}
		std::string packet("[server]: coucou ceci est un packet !");
		server.sendPacket(packet.c_str(), packet.length());
	}
	if (argc == 3)
	{
		// client
		Connection client(_PROTOCOL_ID);
		std::string addr(std::string(argv[1]) + ':' + std::string(argv[2]));
		if (!client.connect(addr))
			return 1;
		std::string packet("[client]: coucou ceci est un packet !");
		client.sendPacket(packet.c_str(), packet.length());
		char ret[100] = {0};
		while (true)
		{
			if (client.receivePacket(ret, 99))
			{
				std::cout << ret << std::endl;
				break;
			}
			my_wait(1);	
		}
	}
	std::cout << "Turning off..." << std::endl;
	Connection::stopConnection();
	return 0;
}