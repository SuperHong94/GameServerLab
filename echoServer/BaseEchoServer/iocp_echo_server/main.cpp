#include "stdafx.h"
using namespace std;
const char* SERVER_IP = "127.0.0.1";
const short SERVER_PORT = 4000;
const int BUFSIZE = 256;

void InitWinSock()
{
   WSADATA wsaData;
   WSAStartup(MAKEWORD(2, 0), &wsaData);//윈도우에서는 호환성때문에 이것을 사용해야한다.
}


int main()
{
   InitWinSock();
   SOCKET s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
   SOCKADDR_IN server_addr;
   ZeroMemory(&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(SERVER_PORT);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   bind(s_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
   listen(s_socket, SOMAXCONN);

   INT addr_size = sizeof(server_addr);
   SOCKET c_socket = WSAAccept(s_socket, reinterpret_cast<sockaddr*>(&server_addr), &addr_size, 0, 0);
   for (;;)
   {

      char recvBuf[BUFSIZE];
      WSABUF mybuf;
      mybuf.buf = recvBuf;
      mybuf.len = BUFSIZE;
      DWORD recv_bytes;
      DWORD recv_flag = 0;
      auto result = WSARecv(c_socket, &mybuf, 1, &recv_bytes, &recv_flag, 0, 0);
	  if (result == SOCKET_ERROR || 0 == recv_bytes)
	  {
		  cout << "WSARecv() Error" << endl;
		  break;
	  }
      cout << "Client Sent: [" << recv_bytes << " bytes] :" << recvBuf << endl;

      mybuf.len = recv_bytes;
      DWORD sent_bytes;
      WSASend(c_socket, &mybuf, 1, &sent_bytes, 0, 0, 0);
   }
   closesocket(s_socket);
   closesocket(c_socket);
   WSACleanup();
}