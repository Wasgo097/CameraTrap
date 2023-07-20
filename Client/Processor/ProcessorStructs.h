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
	std::optional<cv::Mat> lowBrightnessCompensationResult;
};
struct DifferenceResult :public ProcessorResultBase
{
	cv::Mat differenceResult;
	std::optional<cv::Mat> lowBrightnessCompensationResultOpt;
};
struct MoveDetectionResult :public ProcessorResultBase
{
	Objects moveDetectionResult;
	std::optional<cv::Mat> lowBrightnessCompensationResultOpt;
};