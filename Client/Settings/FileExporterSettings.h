#pragma once
#include <nlohmann/json.hpp>
struct FileExporterSettings
{
	std::string outputDirectory;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FileExporterSettings, outputDirectory)