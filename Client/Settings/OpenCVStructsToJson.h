#pragma once
#include <opencv2/core/types.hpp>
#include <nlohmann/json.hpp>
namespace cv {
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Size, width, height)
}