#include "FastLowBrightnessCompensationProcessor.h"
#include <time.h>
#include <opencv2/imgproc.hpp>
void FastLowBrightnessCompensationProcessor::SetInput(std::shared_ptr<IFrame> input)
{
	_result.pRawFrame = std::move(input);
}

LowBrightnessCompensationResult FastLowBrightnessCompensationProcessor::Process()
{
	if (CheckProcessingConditions())
	{
		cv::normalize(_result.pRawFrame->GetMatCRef(), _buffer, 0, 255, cv::NORM_MINMAX);
		_result.lowBrightnessCompensationResultOpt = std::move(_buffer);
	}
	return _result;
}

void FastLowBrightnessCompensationProcessor::Notify(std::shared_ptr<IFrame> param)
{
	SetInput(std::move(param));
	NotifyAllObservers(Process());
}

bool FastLowBrightnessCompensationProcessor::CheckProcessingConditions() const
{
	auto timeTPoint{ std::chrono::system_clock::to_time_t(std::chrono::time_point<std::chrono::system_clock>(_result.pRawFrame->GetTime().time_since_epoch())) };
	std::tm tmTime;
	localtime_s(&tmTime, &timeTPoint);
	return tmTime.tm_hour >= 20 or tmTime.tm_hour < 6;
}