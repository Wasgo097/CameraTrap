#include "VideoSourcesManager.h"

VideoSourcesManager::VideoSourcesManager(std::vector<std::shared_ptr<IVideoSource>>&& videoSources) :_videoSources{ std::move(videoSources) }
{
}

std::unordered_map<std::string, std::shared_ptr<IFrame>> VideoSourcesManager::GetFramesFromSources()const
{
	std::unordered_map<std::string, std::shared_ptr<IFrame>> frames;
	for (const auto& pVideoSource : _videoSources)
		frames.insert({ pVideoSource->GetId(),pVideoSource->GetNextFrame() });
	return frames;
}
size_t VideoSourcesManager::GetVideoSourcesCount()const
{
	return _videoSources.size();
}
