#include "stdafx.h"
#include "Server.h"
#include "NetworkInit.h"
#include "Socket.h"
#include "IPAddress.h"
network::Server::Server(const char* ip, short port , int type)
{
	m_pNetworkInit = std::make_unique<NetworkInit>();
	m_pServerSocket = std::make_unique<Socket>(type);
	m_pIpAddress = std::make_unique<IPAddress>(ip, port);

	_Bind();
}

bool network::Server::_Bind()
{
	::bind(m_pServerSocket->GetSocket(), m_pIpAddress->getRawAddress(), sizeof(struct sockaddr_in));
	return false;
}
