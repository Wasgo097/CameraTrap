#include "VideoSourcesManager.h"

VideoSourcesManager::VideoSourcesManager(std::vector<std::shared_ptr<IVideoSource>>&& videoSources) :_videoSources{ std::move(videoSources) }
{
	_drawingMats.reserve(_videoSources.size());
	for (const auto& videoSource : _videoSources)
		_drawingMats.push_back(ThreadsResourceVal<cv::Mat>(cv::Mat()));
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

const std::vector<std::shared_ptr<IVideoSource>>& VideoSourcesManager::GetVideoSources() const
{
	return _videoSources;
}

const cv::Mat& VideoSourcesManager::GetMatFromBuffer(size_t index) const
{
	if (_drawingMats.size() > index)
	{
		auto& _drawingMat{ _drawingMats[index] };
		std::shared_lock lock(*_drawingMat._pMtx);
		return _drawingMat._val;
	}
	return cv::Mat();
}

void VideoSourcesManager::StartStreaming()
{
	_videoSourcesThreads.reserve(_videoSources.size());
	size_t index{ 0ull };
	for (const auto& videoSource : _videoSources)
	{
		_videoSourcesThreads.push_back(std::make_unique<std::jthread>([videoSource](const std::stop_token& stopToken, ThreadsResourceVal<cv::Mat>& buffer)
			{
				while (!stopToken.stop_requested())
				{
					std::unique_lock lock(*buffer._pMtx);
					auto frame{ videoSource->GetNextFrame() };
					buffer = frame->GetMatCopy();
					videoSource->NotifyAllObservers(frame);
				}
			}, _videoSourcesThreadsStopToken.get_token(), std::ref(_drawingMats[index])));
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
