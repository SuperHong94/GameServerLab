#include <iostream>
#include <WS2tcpip.h>
#include <MSWSock.h>
#include <atomic>
#include <mutex>


#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")
constexpr int BUFSIZE = 512;
constexpr short SERVER_PORT = 4000;
////rio callbackTable
//RIO_CQ g_CQ = 0;
//


/*
RIO���� �ʿ��Ѱ� �����غ���.
RIO_EXTENSION_FUNCTION_TABLE
RIO_CQ g_cq
*/
RIO_EXTENSION_FUNCTION_TABLE g_RIO_Table;
RIO_CQ g_cq;

HANDLE g_iocp = 0;
SOCKET g_serverSocket = 0;
constexpr DWORD g_cqSize = 52;

enum IOTYPE
{
	READ = 0,
	WRITE
};

class RIOBuffer :public ::_RIO_BUF
{
public:
	RIOBuffer() :_RIO_BUF()
	{
		ZeroMemory(buf, BUFSIZE);
	}

	void Alloc()
	{
		if()
	}
private:
	
	char buf[BUFSIZE];
};

class RIOSocket
{
public:

	RIOSocket() = delete;
	RIOSocket(SOCKET sock) :_recvBuffer()
	{
		_rawSocket = sock;
		_rioRQ=g_RIO_Table.RIOCreateRequestQueue(_rawSocket, 32, 1, 32, 1, g_cq, g_cq, NULL);
	}
	~RIOSocket();
	void OnRecv()
	{
		/*g_RIO_Table.RIOReceive(_rioRQ,)*/
	}
	void OnSend()
	{

	}



private:
	SOCKET _rawSocket;
	RIOBuffer _recvBuffer;
	RIO_RQ _rioRQ;
	std::mutex m_L;
};


void Accept(sockaddr* addr, int* addrlen)
{
	for (;;)
	{
		SOCKET csock = ::accept(g_serverSocket, addr, addrlen);


	}
}

int main()
{
	WSAData wsadata;
	WSAStartup(MAKEWORD(2, 0), &wsadata);


	//���ϱ���ü ����
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int addrSize = sizeof(server_addr);

	g_serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED);

	//bind
	bind(g_serverSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));

	//listen
	listen(g_serverSocket, SOMAXCONN);

	//IOCP �����
	g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	//IOCP���

	OVERLAPPED* over = new OVERLAPPED;
	memset(over, 0, sizeof(OVERLAPPED));
	RIO_NOTIFICATION_COMPLETION rioNotiy;
	rioNotiy.Type = RIO_IOCP_COMPLETION; //�ϷḦ IOCP�� �ޱ�
	rioNotiy.Iocp.IocpHandle = g_iocp;
	rioNotiy.Iocp.CompletionKey = reinterpret_cast<PVOID>(1);
	rioNotiy.Iocp.Overlapped = over;

	g_cq = g_RIO_Table.RIOCreateCompletionQueue(g_cqSize, &rioNotiy);
	//SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED);


	SOCKET c_socket = accept(g_serverSocket, reinterpret_cast<sockaddr*>(&server_addr), &addrSize);


}