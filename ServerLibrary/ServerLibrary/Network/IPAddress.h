#pragma once
namespace network
{
	class IPAddress
	{
		sockaddr_in addr;
	public:
		IPAddress(const char* ip, short port);
		struct sockaddr* getRawAddress() { return (struct sockaddr*)&addr; }
	};

}