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

std::vector<std::string> VideoSourcesManager::GetVideoSourcesIds() const
{
	auto count{ GetVideoSourcesCount() };
	std::vector<std::string> ids(count);
	for (size_t i{ 0ull }; i < count; i++)
		ids[i] = _videoSources[i]->GetId();
	return ids;
}
