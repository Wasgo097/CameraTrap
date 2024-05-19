#pragma once
#include <nlohmann/json.hpp>
struct UdpExporterSettings
{
	std::string udpServerIp;
	std::string serverPort;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UdpExporterSettings, udpServerIp, serverPort)