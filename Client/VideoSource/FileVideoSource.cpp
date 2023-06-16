#include "FileVideoSource.h"
#include "FrameBase.h"
#include <opencv2/imgproc.hpp>
FileVideoSource::FileVideoSource(FileVideoSourceSettings settings) :_settings{ settings }
{
	_capture.open(_settings.path);
	if (!_capture.isOpened())
		throw std::runtime_error(std::format("Can't open FileVideoSource with file = {}", settings.path).c_str());
}

std::shared_ptr<IFrame> FileVideoSource::GetNextFrame()
{
	_frameNumber++;
	if (!_capture.read(_buffer) and _settings.loop)
	{
		_capture.set(cv::CAP_PROP_POS_FRAMES, .0);
		_capture.read(_buffer);
	}
	if (_buffer.empty())
		return {};
	if (_settings.gray)
	{
		cv::cvtColor(_buffer, _bufferGray, cv::COLOR_BGR2GRAY);
		return std::make_shared<FrameBase>(_bufferGray.clone(), _frameNumber);
	}
	return std::make_shared<FrameBase>(_buffer.clone(), _frameNumber);
}

std::string FileVideoSource::GetId() const
{
	return _settings.path;
}
