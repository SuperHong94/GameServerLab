#pragma once


namespace network
{
template<typename SOCKET = class RIOSOCKET>
class Server
{
protected:
	std::unique_ptr<class NetworkInit> m_pNetworkInit{};
	std::unique_ptr<SOCKET> m_pServerSocket{};
	std::unique_ptr<class IPAddress> m_pIpAddress{};
	bool _Bind(); 
public:
	Server(const char* ip, short port);

	virtual bool Accept() = 0;
	virtual bool Run() = 0;
	virtual bool Init() = 0;
	virtual ~Server() {};
};

}

