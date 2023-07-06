#pragma once
#include "Utilities/Objects.h"
#include <opencv2/core/mat.hpp>
struct DifferenceResult
{
	cv::Mat differenceResult;
};

struct MoveDetectionResult
{
	Objects moveDetectionResult;
};