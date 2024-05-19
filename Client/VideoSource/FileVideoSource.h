#pragma once
#include <opencv2/videoio.hpp>
#include "Settings/FileVideoSourceSettings.h"
#include "Interfaces/IVideoSource.h"
class FileVideoSource :public IVideoSource
{
public:
	FileVideoSource(FileVideoSourceSettings settings);
	// Inherited via IVideoSource
	virtual std::string GetId() const override;
	std::shared_ptr<IFrame> GetNextFrame() override;
protected:
	cv::VideoCapture _capture;
	cv::Mat _buffer;
	cv::Mat _bufferGray;
	unsigned _frameNumber{ 0u };
	FileVideoSourceSettings _settings;
};