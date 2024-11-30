#pragma once
#include "SocketCRTP.h"

constexpr int MAX_BUFFER_SIZE = 1024;
enum IO_OPERATION
{
	IO_READ,
	IO_WRITE
};
class IocpTcpSocketImpl :public SocketCRTP<IocpTcpSocketImpl>
{
	WSAOVERLAPPED m_overlapped;
	WSABUF m_wsaBuf;
	char m_buffer[MAX_BUFFER_SIZE];
public:
	virtual ~IocpTcpSocketImpl();
	bool SendImpl(const char* buffer, const size_t buffSize);
	bool RecvImpl(const char* buffer, const size_t buffSize);
};