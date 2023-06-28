#pragma once
#include "DifferenceProcessor.h"
#include "MoveDetectorProcessor.h"
#include <memory>
struct Processors
{
	std::shared_ptr<DifferenceProcessor> _pDifferenceProcessor;
	std::shared_ptr<MoveDetectorProcessor> _pMoveDetectorProcessor;
};