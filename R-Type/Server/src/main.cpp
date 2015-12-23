//
// main.cpp for rtype-server in /home/Opcoz/rendu/rtype/R-Type/Server/src
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Wed Dec  9 16:42:05 2015 tran_0
// Last update Wed Dec  9 16:42:05 2015 tran_0
//

#define DEBUG
#include "Server.hh"

int	main(int ac, char **av)
{
  int	port = -1;

  if (ac >= 2)
    std::istringstream(std::string(av[1])) >> port;
  if (ac < 2 || port < 1)
    {
      std::cerr << "Usage: " << av[0] << " [port]" << std::endl;
      return (-1);
    }
  try
    {
      Server			server(port);

	  std::cout << std::boolalpha << "TCPConnection : " << TCPConnection::initConnection() << std::endl;
	  std::cout << WSAGetLastError() << std::endl;
	  std::cout << "[Main] --- Running Server " << std::endl;
	  server.run();
	  std::cout << "[Main] --- Stopping Server " << std::endl;
	  TCPConnection::stopConnection();
  }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return (0);
}
