#include <iostream>
#include <WS2tcpip.h>//2는 버전임


#pragma comment(lib, "ws2_32.lib")

const char* SERVER_IP = "127.0.0.1";
constexpr int BUFSIZE = 512;
constexpr short SERVER_PORT = 4000;

//RIO_EXTENSION_FUNCTION_TABLE g_rio; //rio callbackTable
//RIO_CQ g_CQ = 0;
//
//HANDLE g_iocp = 0;

/*
RIO에서 필요한것 생각해보자.

*/
SOCKET g_clientSocket = 0;
int main()
{
	WSAData wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);
	g_clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, 0);

	//소켓구조체 설정
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);

	inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr.s_addr);
	/*server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);*/

	//listen

	int addr_size = sizeof(server_addr);

	//accept socket
	::connect(g_clientSocket, reinterpret_cast<sockaddr*>(&server_addr), addr_size);



	//recv/send
	for (;;)
	{
		{
			char buf[BUFSIZE];
			WSABUF wsabuf;
			wsabuf.buf = buf;
			wsabuf.len = BUFSIZE;
			DWORD IoBytes = 0;
			DWORD IoFlags = 0;
			std::cout << "send Message : ";

			std::cin.getline(buf, BUFSIZE);
			wsabuf.buf = buf;
			wsabuf.len = strlen(buf) + 1;//null문자까지 세기

			WSASend(g_clientSocket, &wsabuf, 1, &IoBytes, IoFlags, 0, 0);
		}
		{
			char recvBuf[BUFSIZE];
			WSABUF wsabuf;
			wsabuf.buf = recvBuf;
			wsabuf.len = BUFSIZE;
			DWORD IoBytes = 0;
			DWORD IoFlags = 0;
			WSARecv(g_clientSocket, &wsabuf, 1, &IoBytes, &IoFlags, 0, 0);

			std::cout << "Server Send :" << recvBuf << '\n';
		}
	}

}