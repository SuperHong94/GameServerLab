#pragma once
#include <memory>
#include <WS2tcpip.h>
#include <MSWSock.h>



#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

namespace network::config
{
	constexpr short SERVER_PORT = 4000;
}

