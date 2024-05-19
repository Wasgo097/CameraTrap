#pragma once
#include <nlohmann/json.hpp>
struct TcpExporterSettings
{
	std::string tcpServerIp;
	int serverPort;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TcpExporterSettings, tcpServerIp, serverPort)