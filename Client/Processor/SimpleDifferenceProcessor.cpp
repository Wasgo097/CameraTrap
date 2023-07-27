#include "SimpleDifferenceProcessor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

SimpleDifferenceProcessor::SimpleDifferenceProcessor(SimpleDifferenceProcessorSettings settings) :_settings{ std::move(settings) }
{
}

void SimpleDifferenceProcessor::SetInput(LowBrightnessCompensationResult input)
{
	_result.pRawFrame = std::move(input.pRawFrame);
	_result.lowBrightnessCompensationResultOpt = std::move(input.lowBrightnessCompensationResultOpt);
	_previousMat = _currentMat;
	if (_result.lowBrightnessCompensationResultOpt)
		_currentMat = *_result.lowBrightnessCompensationResultOpt;
	else
		_currentMat = _result.pRawFrame->GetMatCRef();
}

DifferenceResult SimpleDifferenceProcessor::Process()
{
	if (_currentMat.empty() or _previousMat.empty())
		return _result;
	GaussianBlur(_currentMat, _currentMatWithBlur, _settings.blurSize, 0);
	GaussianBlur(_previousMat, _previousMatWithBlur, _settings.blurSize, 0);
	cv::absdiff(_currentMatWithBlur, _previousMatWithBlur, _difference);
	cv::threshold(_difference, _result.differenceResult, _settings.threshold, 255, cv::THRESH_BINARY);
	return _result;
}

void SimpleDifferenceProcessor::Notify(LowBrightnessCompensationResult param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}
