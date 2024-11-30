#include "stdafx.h"
#include "NetConfigManager.h"


namespace Network
{
	void NetConfigManager::LoadConfig()
	{
		m_configMap[NetConfigType::PORT] = 4000;
		m_configMap[NetConfigType::IP] = "127.0.0.1";
	}

	std::optional<ConfigValueTypes> NetConfigManager::GetConfigValue(NetConfigType type)
	{
		if (const auto iter = m_configMap.find(type); iter != m_configMap.end())
		{
			return iter->second;
		}
		else
		{
			throw std::runtime_error("Invalid Config Type");
		}
		return {};
	}

} // namespace Network