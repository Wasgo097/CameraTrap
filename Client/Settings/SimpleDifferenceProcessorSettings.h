#pragma once
#include "OpenCVStructsToJson.h"
struct SimpleDifferenceProcessorSettings
{
	cv::Size blurSize;
	int threshold{ 0 };
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SimpleDifferenceProcessorSettings, blurSize, threshold)