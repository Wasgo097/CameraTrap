#include "DifferenceProcessor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

DifferenceProcessor::DifferenceProcessor(DifferenceProcessorSettings settings) :_settings{ std::move(settings) }
{
}

void DifferenceProcessor::AddNewFrame(std::shared_ptr<IFrame> newFrame)
{
	_previousImage = std::move(_currentImage);
	_currentImage = std::move(newFrame);
}

void DifferenceProcessor::Process()
{
	if (not _currentImage or not _previousImage)
		return;
	GaussianBlur(_currentImage->GetMatCRef(), _currentMat, _settings.blurSize, 0);
	GaussianBlur(_previousImage->GetMatCRef(), _previousMat, _settings.blurSize, 0);
	cv::absdiff(_currentMat, _previousMat, _difference);
	cv::threshold(_difference, _treshold, _settings.threshold, 255, cv::THRESH_BINARY);
}

cv::Mat DifferenceProcessor::GetResult() const
{
	return _treshold.clone();
}
