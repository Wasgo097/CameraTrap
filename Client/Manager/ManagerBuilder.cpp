#include "ManagerBuilder.h"
#include "VideoSource/VideoSourceBuilder.h"
#include "Processor/ProcessorBuilder.h"
#include "Processor/DifferenceProcessor.h"
#include "Processor/MoveDetectorProcessor.h"
ManagerBuilder::ManagerBuilder(const MainSettings& mainSettings, std::shared_ptr<ClientAppContext> pClientAppContext) :
	_mainSettings{ mainSettings },
	_pClientAppContext{ std::move(pClientAppContext) }
{}

std::unique_ptr<CalculationManager> ManagerBuilder::BuildCalculationManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultBuffer) const
{
	auto pVideoSourcesManager{ BuildVideoSourcesManager() };
	if (!pVideoSourcesManager)
		throw std::invalid_argument(std::format("VideoSourcesManager is null in CalculationManager").c_str());
	const auto& videoSources{ pVideoSourcesManager->GetVideoSources() };
	auto pProcessorsManager{ BuildProcessorsManager(videoSources,processingResultBuffer) };
	if (!pProcessorsManager)
		throw std::invalid_argument(std::format("ProcessorsManager is null in CalculationManager").c_str());
	return std::make_unique<CalculationManager>(std::move(pVideoSourcesManager), std::move(pProcessorsManager));
}

std::unique_ptr<VideoSourcesManager> ManagerBuilder::BuildVideoSourcesManager() const
{
	VideoSourceBuilder videoSourceBuilder(_mainSettings.settingsRootDir);
	return std::make_unique<VideoSourcesManager>(videoSourceBuilder.BuildVideoSources(_mainSettings.videoSourceSettingsPaths));
}

std::unique_ptr<ProcessorsManager> ManagerBuilder::BuildProcessorsManager(const std::vector<std::shared_ptr<IVideoSource>>& videoSources,
	const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultBuffer) const
{
	std::vector<Processors> processors(videoSources.size());
	ProcessorBuilder processorBuilder(_mainSettings.settingsRootDir);
	size_t index{ 0ull };
	for (auto& processor : processors)
	{
		processor._pDifferenceProcessor = processorBuilder.BuildProcessorWithSettings<DifferenceProcessor, DifferenceProcessorSettings, DifferenceResult, std::shared_ptr<IFrame>>
			(_mainSettings.differenceProcessorSettingsPath);
		processor._pMoveDetectorProcessor = processorBuilder.BuildProcessorWithSettings<MoveDetectorProcessor, MoveDetectorProcessorSettings, MoveDetectionResult, DifferenceResult>
			(_mainSettings.moveDetectorProcessorSettingsPath);
		videoSources[index]->AddNewObserver(processor._pDifferenceProcessor);
		processor._pDifferenceProcessor->AddNewObserver(processor._pMoveDetectorProcessor);
		processor._pMoveDetectorProcessor->AddNewObserver(processingResultBuffer[index]);
		index++;
	}
	return std::make_unique<ProcessorsManager>(std::move(processors));
}

std::unique_ptr<InputManager> ManagerBuilder::BuildInputManager() const
{
	return std::make_unique<InputManager>(_pClientAppContext);
}