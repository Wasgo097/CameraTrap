#pragma once
#include <nlohmann/json.hpp>
struct FileVideoSourceSettings
{
	std::string path;
	bool gray{ false };
	bool loop{ false };
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FileVideoSourceSettings, path, gray, loop)