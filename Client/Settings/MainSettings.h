#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
struct MainSettings
{
	std::string settingsRootDir;
	std::vector<std::string> videoSourceSettingsPaths;
	std::string differenceProcessorSettingsPath;
	std::string moveDetectorProcessorSettingsPath;
	std::string lowBrightnessCompensationProcessorSettingsPath;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MainSettings, settingsRootDir, videoSourceSettingsPaths, differenceProcessorSettingsPath, moveDetectorProcessorSettingsPath, lowBrightnessCompensationProcessorSettingsPath)