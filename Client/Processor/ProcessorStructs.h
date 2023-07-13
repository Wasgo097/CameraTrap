#pragma once
#include "Utilities/Objects.h"
#include <opencv2/core/mat.hpp>
struct DifferenceResult
{
	cv::Mat rawMat;
	cv::Mat differenceResult;
};

struct MoveDetectionResult
{
	cv::Mat rawMat;
	Objects moveDetectionResult;
};