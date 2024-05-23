#include "RtspVideoSource.h"
#include "FrameBase.h"
#include <opencv2/imgproc.hpp>
RtspVideoSource::RtspVideoSource(RtspVideoSourceSettings settings) :_settings{ std::move(settings) }
{
	auto url{ std::format("rtsp://{}:{}@{}:{}/{}",_settings.login,_settings.password,_settings.ip,_settings.port,_settings.variant) };
	_capture.open(url);
	if (!_capture.isOpened())
		throw std::runtime_error(std::format("Can't open RtspVideoSource. Url {}", url).c_str());
}

std::shared_ptr<IFrame> RtspVideoSource::GetNextFrame()
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

std::string RtspVideoSource::GetId() const
{
	return _settings.ip;
}