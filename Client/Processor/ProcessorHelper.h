#pragma once
#include "Interfaces/IProcessor.h"
#include "Interfaces/IFrame.h"
#include "ProcessorStructs.h"
#include <memory>

struct Processors
{
	std::shared_ptr<IProcessor<DifferenceResult, std::shared_ptr<IFrame>>> _pDifferenceProcessor;
	std::shared_ptr<IProcessor<MoveDetectionResult, DifferenceResult>> _pMoveDetectorProcessor;
};