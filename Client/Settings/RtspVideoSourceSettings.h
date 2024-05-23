#pragma once
#include <nlohmann/json.hpp>
#include <string>
struct RtspVideoSourceSettings
{
	std::string login, password, ip, port, variant;
	bool gray;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RtspVideoSourceSettings, login, password, ip, port, variant, gray)