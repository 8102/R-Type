#include "TCPConnection.hh"
#include <stdlib.h>

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
		std::cout << "Connection etablished maggle" << std::endl;
		char msg[11] = { "Bonjourno\n" };
		client.sendPacket(msg, 10);
		std::cout << "Message envoyé !" << std::endl;
		char ret[23] = {0};
		client.receivePacket(ret, 22);
		std::cout << "j'ai recu: [" << ret << "]" << std::endl;
		std::cout << "Ciou !" << std::endl;
	}
	std::cout << "Turning off..." << std::endl;
	TCPConnection::stopConnection();
	return 0;
}