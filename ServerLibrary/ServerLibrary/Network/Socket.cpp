#include "stdafx.h"
#include "Socket.h"
#include "IPAddress.h"


namespace network
{
	inline const SOCKET& Socket::GetSocket() const noexcept
	{
		return sock;
		// TODO: ���⿡ return ���� �����մϴ�.
	}
}