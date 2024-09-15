#include "stdafx.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>//2는 버전임

using namespace std;
#pragma comment(lib, "WS2_32.LIB")

constexpr std::string_view SERVER_IP = "127.0.0.1";
constexpr short SERVER_PORT = 4000;
constexpr int BUFSIZE = 256;

int main()
{
	WSADATA wsaData{};
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	SOCKET socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
	SOCKADDR_IN serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	bind(socket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
	listen(socket, SOMAXCONN);

	int addrSize = sizeof(serverAddr);
	SOCKET clientSocket = WSAAccept(socket, reinterpret_cast<sockaddr*>(&serverAddr), &addrSize, 0, 0);

	for (;;)
	{
		char recvBuf[BUFSIZE]{};
		WSABUF myBuf{ };
		myBuf.buf = recvBuf;
		myBuf.len = BUFSIZE;
		DWORD recvBytes = {};
		DWORD recvFlag = {};
		WSARecv(clientSocket, &myBuf, 1, &recvBytes, &recvFlag, 0, 0);
		cout << "Client Msg : [" << recvBytes << " bytes] :" << recvBuf << '\n';

		myBuf.len = recvBytes;
		DWORD sentBytes{};
		WSASend(clientSocket, &myBuf, 1, &sentBytes, 0, 0, 0);
	}
	closesocket(clientSocket);
	closesocket(socket);
	WSACleanup();



}