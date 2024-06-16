#pragma once

namespace network
{
	class BaseSocketFactory
	{
	public:
		
		std::shared_ptr<class SOCKET> CreateSocket();

	};
}

