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
RIO에서 필요한것 생각해보자.
RIO_EXTENSION_FUNCTION_TABLE
RIO_CQ g_cq
*/


//RIO 기능등록을 위한 table 
RIO_EXTENSION_FUNCTION_TABLE g_RIO_Table;
GUID functionTableId = WSAID_MULTIPLE_RIO;

//전역 cq
RIO_CQ g_cq;

HANDLE g_iocp = 0;
SOCKET g_serverSocket = 0;
constexpr DWORD g_cqSize = 52;

constexpr int MAX_PENDING_RECEIVES = 256;

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

	void Alloc(const size_t size)
	{
		return;
	}

public:
	
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
	WORD wVersionRequested = 0x202;
	if(0!=WSAStartup(wVersionRequested, &wsadata))
	{
		return;
	}

	

	g_serverSocket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED);

	DWORD dwBytes = 0;
	if (S_OK != WSAIoctl(g_serverSocket, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER, &functionTableId, sizeof(GUID), (void**)&g_RIO_Table, sizeof(g_RIO_Table), &dwBytes, 0, 0))
	{
		return; 
	}


	//IOCP 만들기
	g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	//IOCP등록

	OVERLAPPED over;
	memset(&over, 0, sizeof(OVERLAPPED));
	RIO_NOTIFICATION_COMPLETION rioNotiy;
	rioNotiy.Type = RIO_IOCP_COMPLETION; //완료를 IOCP로 받기
	rioNotiy.Iocp.IocpHandle = g_iocp;
	rioNotiy.Iocp.CompletionKey = reinterpret_cast<PVOID>(1);
	rioNotiy.Iocp.Overlapped = &over;

	g_cq = g_RIO_Table.RIOCreateCompletionQueue(g_cqSize, &rioNotiy);
	//SOCKET c_socket = WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED);

	//소켓구조체 설정
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int addrSize = sizeof(server_addr);

	//bind
	bind(g_serverSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));

	//listen
	listen(g_serverSocket, SOMAXCONN);
	SOCKET c_socket = accept(g_serverSocket, reinterpret_cast<sockaddr*>(&server_addr), &addrSize);

	ULONG maxOutstandingReceive = 4;
	ULONG maxReceiveDataBuffers = 1;
	ULONG maxOutstandingSend = 4;
	ULONG maxSendDataBuffers = 1;

	void* pContext = 0;
	RIO_RQ requestQueue = g_RIO_Table.RIOCreateRequestQueue(g_serverSocket, MAX_PENDING_RECEIVES, 1, MAX_PENDING_RECEIVES, 1, g_cq, g_cq, NULL);

	
	//accept
	while (true) {
		sockaddr_in clientAddr;
		int clientAddrSize = sizeof(clientAddr);
		SOCKET clientSocket = accept(g_serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);

		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
			continue;
		}

		// Register the accepted socket
		RIO_RQ clientRequestQueue = g_RIO_Table.RIOCreateRequestQueue(clientSocket, MAX_PENDING_RECEIVES, 1, MAX_PENDING_RECEIVES, 1, g_cq, g_cq, NULL);
		if (clientRequestQueue == RIO_INVALID_RQ) {
			std::cerr << "RIOCreateRequestQueue failed for client: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			continue;
		}

		// Receive loop for the accepted socket
		std::vector<RIO_BUF_INFO> bufferInfos(MAX_PENDING_RECEIVES);
		for (auto& bufferInfo : bufferInfos) {
			bufferInfo.rioBuffer.BufferId = rioExtensionFunctions.RIORegisterBuffer(reinterpret_cast<PCHAR>(&bufferInfo.rawData), BUFFER_SIZE);
			bufferInfo.rioBuffer.Offset = 0;
			bufferInfo.rioBuffer.Length = BUFFER_SIZE;
		}

		for (const auto& bufferInfo : bufferInfos) {
			rioExtensionFunctions.RIOReceive(clientRequestQueue, &bufferInfo.rioBuffer, 1, 0, (PVOID)&bufferInfo);
		}
	}


}