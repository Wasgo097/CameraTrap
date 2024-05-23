#pragma once
#include <opencv2/videoio.hpp>
#include "Settings/RtspVideoSourceSettings.h"
#include "Interfaces/IVideoSource.h"
class RtspVideoSource:public IVideoSource
{
public:
	RtspVideoSource(RtspVideoSourceSettings settings);
	// Inherited via IVideoSource
	std::string GetId() const override;
	std::shared_ptr<IFrame> GetNextFrame() override;
protected:
	cv::VideoCapture _capture;
	cv::Mat _buffer;
	cv::Mat _bufferGray;
	unsigned _frameNumber{ 0u };
	RtspVideoSourceSettings _settings;
};

