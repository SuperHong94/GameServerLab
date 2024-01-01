#include "stdafx.h"
#include "Socket.h"
#include "IPAddress.h"


namespace network
{
	inline const SOCKET& Socket::GetSocket() const noexcept
	{
		return sock;
		// TODO: 여기에 return 문을 삽입합니다.
	}
}