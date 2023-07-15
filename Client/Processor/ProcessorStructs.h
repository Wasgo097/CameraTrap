#pragma once
#include "Utilities/Objects.h"
#include <Interfaces/IFrame.h>
#include <opencv2/core/mat.hpp>
struct DifferenceResult
{
	std::shared_ptr<IFrame> rawFrame;
	cv::Mat differenceResult;
};

struct MoveDetectionResult
{
	std::shared_ptr<IFrame> rawFrame;
	Objects moveDetectionResult;
};