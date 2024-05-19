#pragma once
#include <nlohmann/json.hpp>
struct CameraVideoSourceSettings
{
	size_t index{ 0 };
	bool gray{ false };
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CameraVideoSourceSettings, index, gray)