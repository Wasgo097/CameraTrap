#include "ManagerBuilder.h"
#include "VideoSource/VideoSourceBuilder.h"
#include "Processor/ProcessorBuilder.h"
#include "Processor/DifferenceProcessor.h"
#include "Processor/MoveDetectorProcessor.h"
ManagerBuilder::ManagerBuilder(const MainSettings& mainSettings, ThreadsResourcePtr<ClientAppContext> pClientAppContext) :
	_mainSettings{ mainSettings },
	_pClientAppContext{ std::move(pClientAppContext) }
{}

std::unique_ptr<CalculationManager> ManagerBuilder::BuildCalculationManager() const
{
	auto videoSourcesManager{ BuildVideoSourcesManager() };
	if (!videoSourcesManager)
		throw std::invalid_argument(std::format("VideoSourcesManager is null in CalculationManager").c_str());
	auto processorsManager{ BuildProcessorsManager(videoSourcesManager) };
	if (!processorsManager)
		throw std::invalid_argument(std::format("ProcessorsManager is null in CalculationManager").c_str());
	return std::make_unique<CalculationManager>(std::move(videoSourcesManager), std::move(processorsManager), _pClientAppContext);
}

std::unique_ptr<VideoSourcesManager> ManagerBuilder::BuildVideoSourcesManager() const
{
	VideoSourceBuilder videoSourceBuilder(_mainSettings.settingsRootDir);
	return std::make_unique<VideoSourcesManager>(videoSourceBuilder.BuildVideoSources(_mainSettings.videoSourceSettingsPaths));
}

std::unique_ptr<ProcessorsManager> ManagerBuilder::BuildProcessorsManager(const std::unique_ptr<VideoSourcesManager>& videoSourcesManager) const
{
	const auto& videoSources{ videoSourcesManager->GetVideoSources() };
	std::vector<Processors> processors(videoSources.size());
	ProcessorBuilder processorBuilder(_mainSettings.settingsRootDir);
	size_t videoSourceIndex{ 0ull };
	for (auto& processor : processors)
	{
		processor._pDifferenceProcessor = processorBuilder.BuildProcessorWithSettings<DifferenceProcessor, DifferenceProcessorSettings, DifferenceResult, std::shared_ptr<IFrame>>
			(_mainSettings.differenceProcessorSettingsPath);
		processor._pMoveDetectorProcessor = processorBuilder.BuildProcessorWithSettings<MoveDetectorProcessor, MoveDetectorProcessorSettings, MoveDetectionResult, DifferenceResult>
			(_mainSettings.moveDetectorProcessorSettingsPath);
		videoSources[videoSourceIndex]->AddNewObserver(processor._pDifferenceProcessor);
		processor._pDifferenceProcessor->AddNewObserver(processor._pMoveDetectorProcessor);
		videoSourceIndex++;
	}
	return std::make_unique<ProcessorsManager>(std::move(processors));
}

std::unique_ptr<InputManager> ManagerBuilder::BuildInputManager() const
{
	return std::make_unique<InputManager>(_pClientAppContext);
}