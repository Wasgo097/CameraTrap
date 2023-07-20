#pragma once
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
#include <memory>

struct Processors
{
	std::shared_ptr<IProcessor <LowBrightnessCompensationResult, std::shared_ptr<IFrame>>> _pLowBrightnessCompensationProcessor;
	std::shared_ptr<IProcessor <DifferenceResult, LowBrightnessCompensationResult>> _pDifferenceProcessor;
	std::shared_ptr<IProcessor <MoveDetectionResult, DifferenceResult>> _pMoveDetectorProcessor;
};