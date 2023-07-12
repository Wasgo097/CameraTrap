#pragma once
#include "Interfaces/IVideoSource.h"
#include "Utilities/ThreadsResource.h"
#include "Utilities/ClientAppContext.h"
#include <unordered_map>
#include <thread>
#include <atomic>
class VideoSourcesManager
{
public:
	VideoSourcesManager(std::vector<std::shared_ptr<IVideoSource>>&& videoSources);
	std::unordered_map<std::string, std::shared_ptr<IFrame>> GetFramesFromSources()const;
	size_t GetVideoSourcesCount()const;
	const std::vector<std::shared_ptr<IVideoSource>>& GetVideoSources()const;
	const cv::Mat& GetMatFromBuffer(size_t index)const;
	void StartStreaming();
	void StopStreaming();
protected:
	std::vector<std::shared_ptr<IVideoSource>> _videoSources;
	std::vector<std::unique_ptr<std::jthread>> _videoSourcesThreads;
	std::vector<ThreadsResourceVal<cv::Mat>> _drawingMats;
	std::stop_source _videoSourcesThreadsStopToken;
};