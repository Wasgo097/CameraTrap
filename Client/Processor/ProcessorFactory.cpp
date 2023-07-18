#include "ProcessorFactory.h"
#include "SimpleDifferenceProcessor.h"
#include "SimpleMoveDetectorProcessor.h"
#include "FastMoveDetectorProcessor.h"
ProcessorFactory::ProcessorFactory(std::string processorSettingsRootPath) :_settingsBuilder{ std::move(processorSettingsRootPath) }
{}

std::shared_ptr<IProcessor<DifferenceResult, std::shared_ptr<IFrame>>> ProcessorFactory::BuildDifferenceProcessor(const std::string& path) const
{
	std::shared_ptr<IProcessor<DifferenceResult, std::shared_ptr<IFrame>>> result;
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