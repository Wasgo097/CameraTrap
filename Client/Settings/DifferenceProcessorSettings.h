#pragma once
#include "OpenCVStructsToJson.h"
struct DifferenceProcessorSettings
{
	cv::Size blurSize;
	int threshold{ 0 };
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DifferenceProcessorSettings, blurSize, threshold)