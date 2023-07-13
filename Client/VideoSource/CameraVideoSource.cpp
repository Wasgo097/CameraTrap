#include "CameraVideoSource.h"
#include "FrameBase.h"
#include <opencv2/imgproc.hpp>
CameraVideoSource::CameraVideoSource(CameraVideoSourceSettings settings) :_settings{ std::move(settings) }
{
	_capture.open(static_cast<int>(_settings.index));
	if (!_capture.isOpened())
		throw std::runtime_error(std::format("Can't open CameraVideoSource with index = {}", settings.index).c_str());
}

std::shared_ptr<IFrame> CameraVideoSource::GetNextFrame()
{
	_frameNumber++;
	_capture.read(_buffer);
	if (_settings.gray)
	{
		cv::cvtColor(_buffer, _bufferGray, cv::COLOR_BGR2GRAY);
		return std::make_shared<FrameBase>(_bufferGray.clone(), _frameNumber);
	}
	return std::make_shared<FrameBase>(_buffer.clone(), _frameNumber);
}

std::string CameraVideoSource::GetId() const
{
	return std::to_string(_settings.index);
}
