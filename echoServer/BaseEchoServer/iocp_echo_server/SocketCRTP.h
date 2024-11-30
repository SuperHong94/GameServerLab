#pragma once
template<class Derived>
class SocketCRTP
{
protected:
	SocketCRTP() = default;
	virtual ~SocketCRTP() = default;
	SOCKET m_socket;
	bool Send(const char* buffer, const size_t buffSize)
	{
		return static_cast<Derived*>(this)->SendImpl(buffer, buffSize);
	}

	bool Recv(const char* buffer, const size_t buffSize)
	{
		return static_cast<Derived*>(this)->RecvImpl(buffer, buffSize);
	}
};

