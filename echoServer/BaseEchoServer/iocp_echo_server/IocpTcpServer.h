#pragma once
class IocpTcpServer
{
public:
	IocpTcpServer();
	~IocpTcpServer();
	void Start();
	void Stop();
private:
	SOCKET m_serverSocket{};
	HANDLE m_iocp{};
	void Accept();
	void WorkerThread();
	void HandleIoCompletion(DWORD dwBytesTransferred, OVERLAPPED* overlapped);
	void HandleIoReadCompletion(DWORD dwBytesTransferred, OVERLAPPED* overlapped);
	void HandleIoWriteCompletion(DWORD dwBytesTransferred, OVERLAPPED* overlapped);
};

