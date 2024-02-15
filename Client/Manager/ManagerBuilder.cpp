#include "ManagerBuilder.h"
#include "VideoSource/VideoSourceBuilder.h"
#include "Processor/ProcessorFactory.h"
#include "Exporter/ExporterBuilder.h"
ManagerBuilder::ManagerBuilder(const MainSettings& mainSettings, std::shared_ptr<ClientAppContext> pContext) :
	_mainSettings{ mainSettings },
	_pContext{ std::move(pContext) }
{}

std::unique_ptr<CalculationManager> ManagerBuilder::BuildCalculationManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultsBuffer) const
{
	auto pVideoSourcesManager{ BuildVideoSourcesManager() };
	if (!pVideoSourcesManager)
		throw std::invalid_argument(std::format("VideoSourcesManager is null in CalculationManager").c_str());
	auto pProcessorsManager{ BuildProcessorsManager(pVideoSourcesManager->GetVideoSources(),processingResultsBuffer) };
	if (!pProcessorsManager)
		throw std::invalid_argument(std::format("ProcessorsManager is null in CalculationManager").c_str());
	return std::make_unique<CalculationManager>(std::move(pVideoSourcesManager), std::move(pProcessorsManager));
}

std::unique_ptr<CalculationResultManager> ManagerBuilder::BuildCalculationResultManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultsBuffer,
	ThreadsResourcePtr<cv::Mat> matToGui) const
{
	ExporterBuilder exporterBuilder(_mainSettings.settingsRootDir);
	return std::make_unique<CalculationResultManager>(processingResultsBuffer, matToGui, _pContext, exporterBuilder.BuildExporter(_mainSettings.exporterSettingsPath));
}

std::unique_ptr<VideoSourcesManager> ManagerBuilder::BuildVideoSourcesManager() const
{
	VideoSourceBuilder videoSourceBuilder(_mainSettings.settingsRootDir);
	return std::make_unique<VideoSourcesManager>(videoSourceBuilder.BuildVideoSources(_mainSettings.videoSourceSettingsPaths));
}

std::unique_ptr<ProcessorsManager> ManagerBuilder::BuildProcessorsManager(const std::vector<std::shared_ptr<IVideoSource>>& videoSources,
	const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultsBuffer) const
{
	std::vector<Processors> processors(videoSources.size());
	ProcessorFactory processorBuilder(_mainSettings.settingsRootDir);
	size_t index{ 0ull };
	for (auto& processor : processors)
	{
		processor._pLowBrightnessCompensationProcessor = processorBuilder.BuildLowBrightnessCompensationProcessor(_mainSettings.lowBrightnessCompensationProcessorSettingsPath);
		processor._pDifferenceProcessor = processorBuilder.BuildDifferenceProcessor(_mainSettings.differenceProcessorSettingsPath);
		processor._pMoveDetectorProcessor = processorBuilder.BuildMoveDetectionResult(_mainSettings.moveDetectorProcessorSettingsPath);
		videoSources[index]->AddNewObserver(processor._pLowBrightnessCompensationProcessor);
		processor._pLowBrightnessCompensationProcessor->AddNewObserver(processor._pDifferenceProcessor);
		processor._pDifferenceProcessor->AddNewObserver(processor._pMoveDetectorProcessor);
		processor._pMoveDetectorProcessor->AddNewObserver(processingResultsBuffer[index]);
		index++;
	}
	return std::make_unique<ProcessorsManager>(std::move(processors));
}

std::unique_ptr<InputManager> ManagerBuilder::BuildInputManager() const
{
	return std::make_unique<InputManager>(_pContext);
}