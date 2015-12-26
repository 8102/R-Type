#include "TCPConnection.hh"
#include <stdlib.h>
#include <sstream>

int main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " [address] [port]" << std::endl;
		return 1;
	}
	TCPConnection::initConnection();
	if (argc == 2)
	{
		// server
		TCPConnection server;
		if (!server.listen(atoi(argv[1])))
			return 1;
		TCPSocket *client = server.accept();
		std::cout << "Client connecté ! j'attends un message de 10 characters..." << std::endl;
		char ret[11] = {0};
		client->receive(ret, 10);
		std::cout << "Le client m'a envoyé : [" << ret << "]" <<  std::endl;
		char msg[] = { "Salut mister client !\n" };
		std::cout << "A mon tour, j'envoie :" << msg << std::endl;
		client->send(msg, 22);
		std::cout << "Allez salut !" << std::endl;
	}
	if (argc == 3)
	{
		// client
		TCPConnection client;
		std::string addr(std::string(argv[1]) + ':' + std::string(argv[2]));
		if (!client.connect(addr))
			return 1;
		std::cout << "Connection etablished" << std::endl;
		while (true)
		{
			std::string msg, buf, finalstr;
			std::vector<std::string> tokens;
			std::getline(std::cin, msg);
			std::stringstream ss(msg);
			while (ss >> buf)
				tokens.push_back(buf);
			for (auto it = tokens.begin(); it != tokens.end(); ++it)
				finalstr.push_back((char)(strtoul(it->c_str(), nullptr, 16)));
			std::cout << "sent: " << client.sendPacket(finalstr.c_str(), finalstr.length()) << std::endl;
			char ret[100] = {0};
			char header[4] = {0};
			client.receivePacket(header, 4);
			unsigned short length = (header[2] << 8) | header[3];
			std::cout << "reponse length: " << length << std::endl;
			client.receivePacket(ret, length - 4);
			std::cout << "[";
			for (int i = 0; i < 4; ++i)
				std::cout << std::hex << (int)(header[i]) << " ";
			for (int i = 0; i < length - 4; ++i)
				std::cout << std::hex << (int)(ret[i]) << " ";
			std::cout << ']' << std::endl;
			std::cout << "    ====" << std::endl;
		}
		// char msg[11] = { "Bonjourno\n" };
		// client.sendPacket(msg, 10);
		// std::cout << "Message envoyé !" << std::endl;
		// char ret[23] = {0};
		// client.receivePacket(ret, 22);
		// std::cout << "j'ai recu: [" << ret << "]" << std::endl;
		// std::cout << "Ciou !" << std::endl;

	}
	std::cout << "Turning off..." << std::endl;
	TCPConnection::stopConnection();
	return 0;
}
