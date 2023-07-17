#pragma once
#include "Settings/SettingsBuilder.h"
#include "SimpleDifferenceProcessor.h"
#include "SimpleMoveDetectorProcessor.h"
#include "ProcessorStructs.h"
class ProcessorFactory
{
public:
	ProcessorFactory(std::string processorSettingsRootPath = "") :_settingsBuilder{ std::move(processorSettingsRootPath) }
	{}
	std::shared_ptr<IProcessor<DifferenceResult, std::shared_ptr<IFrame>>> BuildDifferenceProcessor(const std::string& path)const
	{
		std::shared_ptr<IProcessor<DifferenceResult, std::shared_ptr<IFrame>>> result;
		if (auto simpleDifferenceProcessorSettings{ _settingsBuilder.GetSettingsFromFile<SimpleDifferenceProcessorSettings>(path) })
			result = std::make_shared<SimpleDifferenceProcessor>(*simpleDifferenceProcessorSettings);
		return result;
	}
	std::shared_ptr<IProcessor<MoveDetectionResult, DifferenceResult>> BuildMotionDetectionResult(const std::string& path)const
	{
		std::shared_ptr<IProcessor<MoveDetectionResult, DifferenceResult>> result;
		if (auto simpleMoveDetectorProcessorSettings{ _settingsBuilder.GetSettingsFromFile<SimpleMoveDetectorProcessorSettings>(path) })
			result = std::make_shared<SimpleMoveDetectorProcessor>(*simpleMoveDetectorProcessorSettings);
		return result;
	}
protected:
	SettingsBuilder _settingsBuilder;
};