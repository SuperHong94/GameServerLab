#include "stdafx.h"
#include "IPAddress.h"

network::IPAddress::IPAddress(const char* ip, short port)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &(addr.sin_addr.s_addr));
}
