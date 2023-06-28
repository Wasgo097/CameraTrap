#include "VideoSourcesManagerBuilder.h"
#include "VideoSource/VideoSourceBuilder.h"
VideoSourcesManagerBuilder::VideoSourcesManagerBuilder(std::string videoSourcesRoot) :_videoSourcesRoot{ std::move(videoSourcesRoot) }
{
}

std::unique_ptr<VideoSourcesManager> VideoSourcesManagerBuilder::BuildVideoSourcesManager(const std::vector<std::string>& videoSourcesPaths) const
{
	VideoSourceBuilder videoSourceBuilder(_videoSourcesRoot);
	return std::make_unique<VideoSourcesManager>(videoSourceBuilder.BuildVideoSources(videoSourcesPaths));
}
