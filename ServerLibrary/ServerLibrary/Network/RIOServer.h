#pragma once
#include "Server.h"

namespace network
{

class RIOServer :public Server<RIOServer>
{

public:
	RIOServer(const char* ip, short port, int type);
	RIOServer() = delete;
	virtual ~RIOServer();

	virtual bool Init() final;
	bool Run() final;

};


}
