#include "stdafx.h"
#include "IocpSocket.h"

IocpTcpSocketImpl::~IocpTcpSocketImpl()
{
}

bool IocpTcpSocketImpl::SendImpl(const char* buffer, const size_t buffSize)
{
	return false;
}

bool IocpTcpSocketImpl::RecvImpl(const char* buffer, const size_t buffSize)
{
	return false;
}
