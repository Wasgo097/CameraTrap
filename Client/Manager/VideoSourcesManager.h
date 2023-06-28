#pragma once
#include "Interfaces/IVideoSource.h"
#include <unordered_map>
class VideoSourcesManager
{
public:
	VideoSourcesManager(std::vector<std::shared_ptr<IVideoSource>>&& videoSources);

	std::unordered_map<std::string, std::shared_ptr<IFrame>> GetFramesFromSources()const;
	size_t GetVideoSourcesCount()const;
	std::vector<std::string> GetVideoSourcesIds()const;
protected:
	std::vector<std::shared_ptr<IVideoSource>> _videoSources;
};

