#include "FastMoveDetectorProcessor.h"
#include <opencv2/imgproc.hpp>

FastMoveDetectorProcessor::FastMoveDetectorProcessor() :
	_result{ .moveDetectionResult = Objects(1,1) }
{
}

void FastMoveDetectorProcessor::SetInput(DifferenceResult input)
{
	_result.pRawFrame = std::move(input.pRawFrame);
	_result.lowBrightnessCompensationResultOpt = std::move(input.lowBrightnessCompensationResultOpt);
	_differenceInput = std::move(input.differenceResult);
}

MoveDetectionResult FastMoveDetectorProcessor::Process()
{
	if (_differenceInput.empty())
		return _result;
	_result.moveDetectionResult.ClearAllObjects();
	cv::findNonZero(_differenceInput, _whitePixels);
	_result.moveDetectionResult.PushNewObject(cv::boundingRect(_whitePixels));
	_whitePixels.clear();
	return _result;
}

void FastMoveDetectorProcessor::Notify(DifferenceResult param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}
