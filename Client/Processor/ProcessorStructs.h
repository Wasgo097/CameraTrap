#pragma once
#include "Utilities/Objects.h"
#include "Interfaces/IFrame.h"
#include <opencv2/core/mat.hpp>
#include <optional>
struct ProcessorResultBase
{
	std::shared_ptr<IFrame> pRawFrame;
};
struct LowBrightnessCompensationResult :public ProcessorResultBase
{
	std::optional<cv::Mat> lowBrightnessCompensationResultOpt;
};
struct DifferenceResult :public LowBrightnessCompensationResult
{
	cv::Mat differenceResult;
};
struct MoveDetectionResult :public LowBrightnessCompensationResult
{
	Objects moveDetectionResult;
};