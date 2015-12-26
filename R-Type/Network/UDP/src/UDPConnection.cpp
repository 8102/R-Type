#include "UDPConnection.hh"

# ifdef DEBUG
	bool UDPConnection::_debug = true;
# else
	bool UDPConnection::_debug = false;
#endif // DEBUG

/*
** 	       Header :
** =========================
**   uint32_t Protocol ID
** =========================
**    size_t Sequence ID
** =========================
**       size_t Ack
** =========================
** 	 uint32_t AckBitField
** =========================
*/

/*
** Constructors / Destructors
*/
UDPConnection::UDPConnection(uint32_t protocolID) :
	_protocolID(protocolID), _state(Disconnected), _header_size(sizeof(header_t)),
	_local_sequence(1), _remote_sequence(0), _last_ack(0), _ack_bitfield(0),
	_acked_bitfield(0), _packet_send(0), _packet_loss(0)
{
}

UDPConnection::UDPConnection(UDPConnection const &other, Address address) :
	_local_sequence(1), _remote_sequence(0), _last_ack(0), _ack_bitfield(0),
	_acked_bitfield(0), _packet_send(0), _packet_loss(0)
{
	if (&other != this)
	{
		_protocolID = other._protocolID;
		_socket = other._socket;
		_address = address;
		_state = Connected;
		_header_size = other._header_size;
	}
}


UDPConnection::~UDPConnection()
{
	if (_socket.isOpen())
		_socket.close();
	while (!_known_connections.empty())
	{
		delete _known_connections.back();
		_known_connections.pop_back();
	}
}

/*
** Setters / Getters
*/

Address const &UDPConnection::getAddress() const
{
	return _address;
}

/*
** Public methodes
*/
bool		UDPConnection::listen(unsigned short port)
{
	if (!_socket.open(port))
	{
		std::cerr << "Can't listen on port: " << port << std::endl;
		return false;
	}
	if (_debug)
		std::cout << "Server listening on port " << port << std::endl;
	_state = Listening;
	_address.setPort(port);
	return true;
}

bool		UDPConnection::connect(std::string const &address)
{
	_address = Address(address);
	if (!_socket.open(_address.getPort(), true))
	{
		if (_debug)
			std::cerr << "Can't connect to " << address << std::endl;
		_address = Address();
		return false;
	}
	if (_debug)
		std::cerr << "Connecting to " << address << "..." <<  std::endl;
	_state = Connecting;
	int auth_token = AUTH_TOKEN;
	this->sendPacket(&auth_token, sizeof(int));
	return true;
}

bool		UDPConnection::connect(unsigned int address, unsigned short port)
{
	_address = Address(address, port);
	if (!_socket.open(port, true))
	{
		if (_debug)
			std::cerr << "Can't connect to : " << _address.toString() << std::endl;
		_address = Address();
		return false;
	}
	if (_debug)
		std::cerr << "Connecting to " << address << "..." <<  std::endl;
	_state = Connecting;
	int auth_token = AUTH_TOKEN;
	this->sendPacket(&auth_token, sizeof(int));
	return true;
}

bool		UDPConnection::sendPacket(void const *data, size_t size)
{
	if (_state == Disconnected || _state == Listening)
		return false;
	std::cout << _remote_sequence << std::endl;
	std::unique_ptr<char[]> packet(new char[size + _header_size]());
	header_t header;
	header.protocolID = _protocolID;
	header.sequenceID = _local_sequence;
	header.ack = _remote_sequence;
	header.ack_bitfield = _ack_bitfield;
	std::memcpy(packet.get(), &header, _header_size);
	std::memcpy(packet.get() + _header_size, data, size);
	++_local_sequence;
	++_packet_send;
	return _socket.send(_address, packet.get(), size + _header_size);
}

bool		UDPConnection::sendPacket(void const *data, size_t size, UDPConnection *to)
{
	_address = to->getAddress();
	return this->sendPacket(data, size);
}

int			UDPConnection::receivePacket(void *data, size_t size, UDPConnection * &client)
{
	if (_state == Disconnected)
		return 0;
	std::unique_ptr<char[]> packet(new char[size + _header_size]());
	Address from;
	int recv_bytes = _socket.receive(from, packet.get(), size + _header_size);
	if (recv_bytes == -1)
		return -1;
	if (recv_bytes <= _header_size)
		return 0;
	header_t	header;
	std::memcpy(&header, packet.get(), _header_size);
	if (header.protocolID != _protocolID)
		return 0;
	this->updateReliability(&header);
	if (_state == Listening)
	{
		bool new_client(true);
		for (auto it = _known_connections.begin(); it != _known_connections.end(); ++it)
		{
			if ((*it)->getAddress() == from)
				new_client = false;
		}
		if (new_client)
		{
			int token(0);
			std::memcpy(&token, packet.get() + _header_size, sizeof(int));
			if (token == AUTH_TOKEN)
			{
				if (_debug)
					std::cout << "New connection from: " << from.toString() << std::endl;
				UDPConnection *new_connection = new UDPConnection(*this, from);
				_new_connections.push_back(new_connection);
				_known_connections.push_back(new_connection);
			}
			return 0;
		}
	}
	for (auto it = _known_connections.begin(); it != _known_connections.end(); ++it)
	{
		if ((*it)->getAddress() == from)
		{
			std::memcpy(data, packet.get() + _header_size, recv_bytes - _header_size);
			client = *it;
			return recv_bytes - _header_size;
		}
	}
	if (_address == from)
	{
		std::memcpy(data, packet.get() + _header_size, recv_bytes - _header_size);
		return recv_bytes - _header_size;
	}
	return 0;
}

int				UDPConnection::receivePacket(void *data, size_t size)
{
	UDPConnection *useless = nullptr;
	return this->receivePacket(data, size, useless);
}

UDPConnection 	*UDPConnection::getNewConnection()
{
	if (_new_connections.empty())
		return nullptr;
	UDPConnection *last = _new_connections.front();
	_new_connections.pop_front();
	return last;
}

void			UDPConnection::broadcast(void *data, size_t size, UDPConnection const *except)
{
	for (auto it = _known_connections.begin(); it != _known_connections.end(); ++it)
	{
		if (except && except->getAddress() != (*it)->getAddress())
			(*it)->sendPacket(data, size);
		if (except == nullptr)
		 	(*it)->sendPacket(data, size);
	}
}

/*
** Privates methode
*/

void 			UDPConnection::updateReliability(header_t *header)
{
//	std::cout << _remote_sequence << std::endl;
	// pas oublier de changer ça. Si je push ça je suis un boloss
	std::cout << header->sequenceID << std::endl;
	if (_remote_sequence < header->sequenceID)
	{
		std::cout << "to" << std::endl;
 		_ack_bitfield <<= header->sequenceID - _remote_sequence;
		SET_BIT(_ack_bitfield, header->sequenceID - _remote_sequence - 1);
		_remote_sequence = header->sequenceID;
		std::cout << "-->" << _remote_sequence << std::endl;
	}
	else
		SET_BIT(_acked_bitfield, _remote_sequence - header->sequenceID - 1);
	if (_last_ack < header->ack)
	{
		for (unsigned short i = 0; i < header->ack - _last_ack; ++i)
		{
			if (GET_BIT(_acked_bitfield, sizeof(_acked_bitfield) - i) == 0)
				++_packet_loss;
		}
		_acked_bitfield <<= header->ack - _last_ack;
		SET_BIT(_ack_bitfield, header->ack - _last_ack - 1);
		_last_ack = header->ack;
	}
	else
		SET_BIT(_acked_bitfield, _last_ack - header->ack - 1);
	for (unsigned short i = 0; i < sizeof(header->ack_bitfield) * BYTE_SIZE; ++i)
	{
		if (header->ack - i - 1 >= _remote_sequence - (sizeof(_acked_bitfield) * BYTE_SIZE))
		{
			char bit = GET_BIT(header->ack_bitfield, i);
			if (bit)
			{
				short j = _remote_sequence - header->ack + i;
				SET_BIT(_acked_bitfield, j);
			}
		}
	}
}

int			UDPConnection::getPacketLoss() const
{
	return _packet_loss / _packet_send * 100;
}
