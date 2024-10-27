#include <iostream>
#include <WS2tcpip.h>//2는 버전임

using namespace std;
#pragma comment(lib,"WS2_32.LIB") //표준에없기에 라이브러리도 추가해야됨

const char* SERVER_IP = "127.0.0.1";

const short SERVER_PORT = 4000;
const int BUFSIZE = 256;
void err_display(int err_num) {
   WCHAR* lpMSgbuf;
   FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, err_num, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPWSTR)&lpMSgbuf, 0, 0);
   wcout << lpMSgbuf << endl;
   while (true);
   LocalFree(lpMSgbuf);

}
int main()
{
   wcout.imbue(locale("korean"));
   WSADATA wsaData;
   WSAStartup(MAKEWORD(2, 0), &wsaData);//윈도우에서는 호환성때문에 이것을 사용해야한다.
   SOCKET s_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
   SOCKADDR_IN server_addr;
   ZeroMemory(&server_addr, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(SERVER_PORT);
   inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
   connect(s_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));

   for (;;) {
      char buf[BUFSIZE];
      cout << "Enter Message : ";
      cin.getline(buf, BUFSIZE);//cin은 워드단위로 받는것이라서 공백이 들어가면 잘린다. Hello world 한번에 못받으니깐 cin.getline()으로 한줄 받게한다.
      WSABUF mybuf;
      mybuf.buf = buf;
      mybuf.len = static_cast<ULONG>(strlen(buf) + 1);//실제로 보낸 사이즈 보내기 ,strlen(buf)하면 마지막 널문자를 안샌다. 그래서 널까지 보내기위해 +1을한다.
      DWORD sent_bytes;
      int ret=WSASend(s_socket, &mybuf, 1, &sent_bytes, 0, 0, 0);
      if (SOCKET_ERROR == ret)
      {
         cout << "Send Error :";
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
      cout << "Server Sent: [" << recv_bytes << " bytes] :" << recvBuf<<endl;
   }
   closesocket(s_socket);
   WSACleanup();
}