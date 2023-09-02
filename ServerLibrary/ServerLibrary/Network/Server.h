#pragma once


namespace network
{

class Server
{
protected:
	std::unique_ptr<class NetworkInit> m_pNetworkInit{};
public:
	Server(const char* ip, short port);

	virtual bool Accept() = 0;
	virtual bool Run() = 0;
	virtual ~Server() {};
};

}

