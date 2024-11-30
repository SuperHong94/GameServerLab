#include "stdafx.h"
#include "IocpTcpServer.h"


void error_display(int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, 0);
	std::wcout<<"[error][Network]" << lpMsgBuf << std::endl;
	while (true);
	LocalFree(lpMsgBuf);
}

IocpTcpServer::IocpTcpServer()
{
	m_serverSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (m_serverSocket == INVALID_SOCKET)
	{
		error_display(WSAGetLastError());
		throw std::runtime_error("WSASocket() failed");
	}

	SOCKADDR_IN serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAdr


}
