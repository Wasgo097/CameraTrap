#include "VideoSourcesManager.h"

VideoSourcesManager::VideoSourcesManager(std::vector<std::shared_ptr<IVideoSource>>&& videoSources) :_videoSources{ std::move(videoSources) }
{
}

const std::vector<std::shared_ptr<IVideoSource>>& VideoSourcesManager::GetVideoSources() const
{
	return _videoSources;
}

void VideoSourcesManager::StartStreaming()
{
	_videoSourcesThreads.reserve(_videoSources.size());
	size_t index{ 0ull };
	for (const auto& videoSource : _videoSources)
	{
		_videoSourcesThreads.push_back(std::make_unique<std::jthread>([videoSource](const std::stop_token& stopToken)
			{
				while (!stopToken.stop_requested())
					videoSource->NotifyAllObservers(videoSource->GetNextFrame());
			}, _videoSourcesThreadsStopToken.get_token()));
		index++;
	}
}

void VideoSourcesManager::StopStreaming()
{
	_videoSourcesThreadsStopToken.request_stop();
	for (const auto& thread : _videoSourcesThreads)
	{
		if (thread->joinable())
			thread->join();
	}
	_videoSourcesThreads.clear();
	_videoSourcesThreadsStopToken = std::stop_source();
}