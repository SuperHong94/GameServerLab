#pragma once
#include "Singleton.h"
// NetWork 관련 설정파일 로드하는 Manager


namespace Network
{
	enum NetConfigType
	{
		PORT = 0,
		IP = 1,
	};
	class NetConfigManager : public Singleton<NetConfigManager>
	{
		using ConfigValueTypes = std::variant<int, std::string>;
		std::unordered_map < NetConfigType, ConfigValueTypes> m_configMap;
	public:
		NetConfigManager() {};
		virtual ~NetConfigManager() {};
		void LoadConfig();
		std::optional< ConfigValueTypes> GetConfigValue(NetConfigType type);
	};
}
