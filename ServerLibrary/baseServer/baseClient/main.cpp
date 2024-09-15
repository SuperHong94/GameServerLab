#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "WS2_32.LIB")

constexpr int BUFSIZE = 256;

void err_display(int err_num) {
	WCHAR* lpMSgbuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_num, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMSgbuf, 0, 0);
	std::wcout << lpMSgbuf << std::endl;
	while (true);
	LocalFree(lpMSgbuf);

}

int main()
{
	std::string serverIp {};
	short serverPort{};
	std::cout << "input serverIP : ";
	std::cin >> serverIp;

	std::cout << "input serverPort: ";
	std::cin >> serverPort;


	std::wcout.imbue(std::locale("korean"));
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);//�����쿡���� ȣȯ�������� �̰��� ����ؾ��Ѵ�.
	SOCKET s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverIp.c_str(), &server_addr.sin_addr);
	connect(s_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));

	for (;;) {
		char buf[BUFSIZE];
		std::cout << "Enter Message : ";
		std::cin.getline(buf, BUFSIZE);//cin�� ��������� �޴°��̶� ������ ���� �߸���. Hello world �ѹ��� �������ϱ� cin.getline()���� ���� �ް��Ѵ�.
		WSABUF mybuf;
		mybuf.buf = buf;
		mybuf.len = static_cast<ULONG>(strlen(buf) + 1);//������ ���� ������ ������ ,strlen(buf)�ϸ� ������ �ι��ڸ� �Ȼ���. �׷��� �α��� ���������� +1���Ѵ�.
		DWORD sent_bytes;
		int ret = WSASend(s_socket, &mybuf, 1, &sent_bytes, 0, 0, 0);
		if (SOCKET_ERROR == ret)
		{
			std::cout << "Send Error :";
			int err_num = WSAGetLastError();
			err_display(err_num);
		}
		char recvBuf[BUFSIZE];
		WSABUF mybuf_r;
		mybuf_r.buf = recvBuf;
		mybuf_r.len = BUFSIZE;
		DWORD recv_bytes;
		DWORD recv_flag = 0;
		WSARecv(s_socket, &mybuf_r, 1, &recv_bytes, &recv_flag, 0, 0);
		std::cout << "Server Sent: [" << recv_bytes << " bytes] :" << recvBuf << std::endl;
	}
	closesocket(s_socket);
	WSACleanup();
}