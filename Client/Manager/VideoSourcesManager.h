#pragma once
#include "Interfaces/IVideoSource.h"
#include "Utilities/MultiThreading/ThreadsResource.h"
#include "Utilities/ClientAppContext.h"
#include <unordered_map>
#include <thread>
class VideoSourcesManager
{
public:
	VideoSourcesManager(std::vector<std::shared_ptr<IVideoSource>>&& videoSources);
	const std::vector<std::shared_ptr<IVideoSource>>& GetVideoSources()const;
	void StartStreaming();
	void StopStreaming();
protected:
	std::vector<std::shared_ptr<IVideoSource>> _videoSources;
	std::vector<std::unique_ptr<std::jthread>> _videoSourcesThreads;
	std::stop_source _videoSourcesThreadsStopToken;
};