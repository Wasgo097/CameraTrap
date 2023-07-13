#pragma once
#include <nlohmann/json.hpp>
struct MoveDetectorProcessorSettings
{
	size_t initBufferSize{ 0 };
	size_t maxObjectsCount{ 0 };
	int minObjectArea{ 0 };
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MoveDetectorProcessorSettings, initBufferSize, maxObjectsCount, minObjectArea)