#pragma once
#include "Interfaces/IVideoSource.h"
#include "Settings/SettingsBuilder.h"
class VideoSourceBuilder
{
public:
	VideoSourceBuilder(std::string videoSourceSettingsPath);
	std::shared_ptr<IVideoSource> BuildVideoSource(const std::string& path)const;
	std::vector<std::shared_ptr<IVideoSource>> BuildVideoSources(const std::vector<std::string>& paths)const;
private:
	SettingsBuilder _settingsBuilder;
};