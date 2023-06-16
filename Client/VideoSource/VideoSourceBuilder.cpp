#include "VideoSourceBuilder.h"
#include "CameraVideoSource.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
VideoSourceBuilder::VideoSourceBuilder(std::string videoSourceSettingsRootPath) :_settingsBuilder{ std::move(videoSourceSettingsRootPath) }
{
}

std::shared_ptr<IVideoSource> VideoSourceBuilder::BuildVideoSource(const std::string& path) const
{
	std::shared_ptr<IVideoSource> result;
	try
	{
		result = std::make_shared<CameraVideoSource>(_settingsBuilder.GetSettingsFromFile<CameraVideoSourceSettings>(path));
	}
	catch (...) {}
	return result;
}

std::vector<std::shared_ptr<IVideoSource>>  VideoSourceBuilder::BuildVideoSources(const std::vector<std::string>& paths) const
{
	std::vector<std::shared_ptr<IVideoSource>> result;
	result.reserve(paths.size());
	for (const auto& path : paths)
		result.push_back(std::move(BuildVideoSource(path)));
	return result;
}