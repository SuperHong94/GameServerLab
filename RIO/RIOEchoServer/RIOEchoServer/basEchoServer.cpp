#include <iostream>
#include <WS2tcpip.h>//2는 버전임


#pragma comment(lib, "ws2_32.lib")

constexpr int BUFSIZE = 512;
constexpr short SERVER_PORT = 4000;
//RIO_EXTENSION_FUNCTION_TABLE g_rio; //rio callbackTable
//RIO_CQ g_CQ = 0;
//
//HANDLE g_iocp = 0;

/*
RIO에서 필요한것 생각해보자.

*/
SOCKET g_serverSocket = 0;
int main()
{
	WSAData wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);
	g_serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);

	//소켓구조체 설정
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//bind
	bind(g_serverSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));

	//listen
	listen(g_serverSocket, SOMAXCONN);

	int addr_size = sizeof(server_addr);

	//accept socket
	SOCKET c_socket = WSAAccept(g_serverSocket, reinterpret_cast<sockaddr*>(&server_addr), &addr_size, 0, 0);


	

	//recv/send
	for (;;)
	{
		char recvBuf[BUFSIZE];
		WSABUF mybuf;
		mybuf.buf = recvBuf;
		mybuf.len = BUFSIZE;
		DWORD recv_bytes = 0;
		DWORD recv_flag = 0;
		WSARecv(c_socket, &mybuf, 1, &recv_bytes, &recv_flag, 0, 0);
		std::cout << "Client Sent: [" << recv_bytes << " bytes] :" << recvBuf << std::endl;

		mybuf.len = recv_bytes;
		DWORD sent_bytes=0;
		WSASend(c_socket, &mybuf, 1, &sent_bytes, 0, 0, 0);
	}

}