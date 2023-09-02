#pragma once

namespace network
{
class NetworkInit
{
public:
	NetworkInit()
	{
		//WSADATA w;
		//WSAStartup(0x202, &w);
	}
	~NetworkInit()
	{
		//WSACleanup();
	}
};
}
