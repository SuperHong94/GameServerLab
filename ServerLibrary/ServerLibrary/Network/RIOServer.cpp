#include "stdafx.h"
#include "RIOServer.h"



network::RIOServer::RIOServer(const char* ip, short port, int type):Server(ip,port, type)
{
	m_pServerSocket;
}


bool network::RIOServer::Init()
{	
	return false;
}

bool network::RIOServer::Run()
{
	return false;
}
