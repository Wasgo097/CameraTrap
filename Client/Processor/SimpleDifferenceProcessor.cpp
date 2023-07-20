#include "SimpleDifferenceProcessor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

SimpleDifferenceProcessor::SimpleDifferenceProcessor(SimpleDifferenceProcessorSettings settings) :_settings{ std::move(settings) }
{
}

void SimpleDifferenceProcessor::SetInput(LowBrightnessCompensationResult input)
{
	_input = std::move(input);
	_previousMat = std::move(_currentMat);
	if (_input.lowBrightnessCompensationResult)
		_currentMat = _input.lowBrightnessCompensationResult->clone();
	else
		_currentMat = _input.pRawFrame->GetMatCopy();
}

DifferenceResult SimpleDifferenceProcessor::Process()
{
	_result.pRawFrame = std::move(_input.pRawFrame);
	_result.lowBrightnessCompensationResultOpt = std::move(_input.lowBrightnessCompensationResult);
	if (_currentMat.empty() or _previousMat.empty())
		return _result;
	GaussianBlur(_currentMat, _currentMat, _settings.blurSize, 0);
	GaussianBlur(_previousMat, _previousMat, _settings.blurSize, 0);
	cv::absdiff(_currentMat, _previousMat, _difference);
	cv::threshold(_difference, _result.differenceResult, _settings.threshold, 255, cv::THRESH_BINARY);
	return _result;
}

void SimpleDifferenceProcessor::Notify(LowBrightnessCompensationResult param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}
