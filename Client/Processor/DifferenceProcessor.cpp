#include "DifferenceProcessor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

DifferenceProcessor::DifferenceProcessor(DifferenceProcessorSettings settings) :_settings{ std::move(settings) }
{
}

void DifferenceProcessor::SetInput(std::shared_ptr<IFrame> newFrame)
{
	_pPreviousImage = std::move(_pCurrentImage);
	_pCurrentImage = std::move(newFrame);
}

DifferenceResult DifferenceProcessor::Process()
{
	if (!_pCurrentImage or !_pPreviousImage)
		return { _pCurrentImage ,{} };
	_pCurrentImage->GetMatCRef().copyTo(_currentMat);
	_pPreviousImage->GetMatCRef().copyTo(_previousMat);
	GaussianBlur(_currentMat, _currentMat, _settings.blurSize, 0);
	GaussianBlur(_previousMat, _previousMat, _settings.blurSize, 0);
	cv::absdiff(_currentMat, _previousMat, _difference);
	cv::threshold(_difference, _treshold, _settings.threshold, 255, cv::THRESH_BINARY);
	return { _pCurrentImage, _treshold };
}

void DifferenceProcessor::Notify(std::shared_ptr<IFrame> param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}
