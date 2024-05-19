#pragma once
#include "Settings/SettingsBuilder.h"
#include "Interfaces/IProcessor.h"
#include "ProcessorStructs.h"
class ProcessorFactory
{
public:
	ProcessorFactory(std::string processorSettingsRootPath = "");
	std::shared_ptr<IProcessor<LowBrightnessCompensationResult, std::shared_ptr<IFrame>>> BuildLowBrightnessCompensationProcessor(const std::string& path)const;
	std::shared_ptr<IProcessor<DifferenceResult, LowBrightnessCompensationResult>> BuildDifferenceProcessor(const std::string& path)const;
	std::shared_ptr<IProcessor<MoveDetectionResult, DifferenceResult>> BuildMoveDetectionResult(const std::string& path)const;
protected:
	const SettingsBuilder _settingsBuilder;
};