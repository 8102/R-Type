# include "UDPConnection.hh"
# include <stdlib.h> // thug life
# include <vector>
# include <time.h>

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
	if (argc != 2 && argc != 3 && argc != 4)
	{
		std::cout << "Usage: " << argv[0] << " [address] [port] [mode_cli]" << std::endl;
		return (1);
	}
	UDPConnection::initConnection();
	if (argc == 2)
	{
		// server
		UDPConnection server(_PROTOCOL_ID);
		if (!server.listen(atoi(argv[1])))
			return 1;
		UDPConnection *from = nullptr;
		while (true)
		{
			char ret[100] = {0};
			int len = server.receivePacket(ret, 99, from);
			if (len > 0)
			{
				std::cout << "kiwi" << server.sendPacket(ret, len, from) << std::endl;
			}
			if (std::string(ret) == "quit")
				break;
		}
	}
	if (argc == 3)
	{
		// client
		UDPConnection client(_PROTOCOL_ID);
		std::string addr(std::string(argv[1]) + ':' + std::string(argv[2]));
		if (!client.connect(addr))
			return 1;
		time_t start = time(NULL);
		// while (true)
		// {
		// 	char ret[100] = {0};
		// 	if (client.receivePacket(ret, 99) != -1)
		// 		std::cout << ret << std::endl;
		// 	if (std::string(ret) == "quit")
		// 		break;
		// 	my_wait(0.1);
		// }
		size_t nbPackets = 0;
		std::string msg("coucou");
		while ((time(NULL) - start) < 5)
		{
			char ret[100] = {0};
			client.sendPacket(msg.c_str(), msg.length());
			client.receivePacket(ret, 99);
			nbPackets += 1;
		}
		std::cout << "packet loss: " << client.getPacketLoss() << std::endl;
	}
	if (argc == 4)
	{
		UDPConnection client(_PROTOCOL_ID);
		std::string addr(std::string(argv[1]) + ':' + std::string(argv[2]));
		if (!client.connect(addr))
			return 1;
		while (true)
		{
			char msg[100] = {0};
			if (client.receivePacket(msg, 99) != -1)
				std::cout << "=> " << msg << std::endl;
			std::string ret;
			std::getline(std::cin, ret);
			std::cout << "jenvois: [" << ret << "]" << std::endl;
			client.sendPacket(ret.c_str(), ret.length());
			if (ret == "quit")
				break;
		}
	}
	std::cout << "Turning off..." << std::endl;
	UDPConnection::stopConnection();
	return 0;
}
