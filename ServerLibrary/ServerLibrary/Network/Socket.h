#pragma once
namespace network
{

class ISocketInterface
{
public:
	virtual std::shared_ptr<SOCKET> CreateSocket() = 0;
	virtual std::shared_ptr<SOCKET> GetSocket() = 0;
	virtual void Listen() = 0;
	virtual void Accept() = 0;

};


}

