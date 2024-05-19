#include "ProcessorFactory.h"
#include "SimpleDifferenceProcessor.h"
#include "SimpleMoveDetectorProcessor.h"
#include "FastMoveDetectorProcessor.h"
#include "FastLowBrightnessCompensationProcessor.h"
ProcessorFactory::ProcessorFactory(std::string processorSettingsRootPath) :_settingsBuilder{ std::move(processorSettingsRootPath) }
{}

std::shared_ptr<IProcessor<LowBrightnessCompensationResult, std::shared_ptr<IFrame>>> ProcessorFactory::BuildLowBrightnessCompensationProcessor(const std::string& path) const
{
	std::shared_ptr<IProcessor<LowBrightnessCompensationResult, std::shared_ptr<IFrame>>> result;
	if (path.empty())
		result = std::make_shared<FastLowBrightnessCompensationProcessor>();
	return result;
}

std::shared_ptr<IProcessor<DifferenceResult, LowBrightnessCompensationResult>> ProcessorFactory::BuildDifferenceProcessor(const std::string& path) const
{
	std::shared_ptr<IProcessor<DifferenceResult, LowBrightnessCompensationResult>> result;
	if (auto simpleDifferenceProcessorSettings{ _settingsBuilder.GetSettingsFromFile<SimpleDifferenceProcessorSettings>(path) })
		result = std::make_shared<SimpleDifferenceProcessor>(*simpleDifferenceProcessorSettings);
	return result;
}

std::shared_ptr<IProcessor<MoveDetectionResult, DifferenceResult>> ProcessorFactory::BuildMoveDetectionResult(const std::string& path) const
{
	std::shared_ptr<IProcessor<MoveDetectionResult, DifferenceResult>> result;
	if (path.empty())
		result = std::make_shared<FastMoveDetectorProcessor>();
	else if (auto simpleMoveDetectorProcessorSettings{ _settingsBuilder.GetSettingsFromFile<SimpleMoveDetectorProcessorSettings>(path) })
		result = std::make_shared<SimpleMoveDetectorProcessor>(*simpleMoveDetectorProcessorSettings);
	return result;
}