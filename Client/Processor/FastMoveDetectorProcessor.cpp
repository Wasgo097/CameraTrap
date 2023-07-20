#include "FastMoveDetectorProcessor.h"
#include <opencv2/imgproc.hpp>

FastMoveDetectorProcessor::FastMoveDetectorProcessor() :
	_result{ .moveDetectionResult = Objects(1,1) }
{
}

void FastMoveDetectorProcessor::SetInput(DifferenceResult input)
{
	_input = std::move(input);
}

MoveDetectionResult FastMoveDetectorProcessor::Process()
{
	_result.pRawFrame = std::move(_input.pRawFrame);
	_result.lowBrightnessCompensationResultOpt = _input.lowBrightnessCompensationResultOpt;
	const auto& differenceMatBuffer{ _input.differenceResult };
	if (differenceMatBuffer.empty())
		return _result;
	_result.moveDetectionResult.ClearAllObjects();
	cv::findNonZero(differenceMatBuffer, _whitePixels);
	_result.moveDetectionResult.PushNewObject(cv::boundingRect(_whitePixels));
	_whitePixels.clear();
	return _result;
}

void FastMoveDetectorProcessor::Notify(DifferenceResult param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}
