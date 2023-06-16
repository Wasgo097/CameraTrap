#pragma once
#include <string>
#include <memory>
#include "VideoSourcesManager.h"
class VideoSourcesManagerBuilder
{
public:
	VideoSourcesManagerBuilder(std::string videoSourcesRoot);
	std::unique_ptr<VideoSourcesManager> BuildVideoSourcesManager(const std::vector<std::string>& videoSourcesPaths)const;
protected:
	std::string _videoSourcesRoot;
};