#pragma once
#include <opencv2/videoio.hpp>
#include "Settings/CameraVideoSourceSettings.h"
#include "Interfaces/IVideoSource.h"
class CameraVideoSource :public IVideoSource 
{
public:
	CameraVideoSource(CameraVideoSourceSettings settings);
	// Inherited via IVideoSource
	std::string GetId() const override;
	std::shared_ptr<IFrame> GetNextFrame() override;
protected:
	cv::VideoCapture _capture;
	cv::Mat _buffer;
	cv::Mat _bufferGray;
	unsigned _frameNumber{ 0u };
	CameraVideoSourceSettings _settings;
};