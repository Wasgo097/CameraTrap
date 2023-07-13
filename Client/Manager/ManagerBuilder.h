#pragma once
#include "VideoSourcesManager.h"
#include "InputManager.h"
#include "CalculationManager.h"
#include "ProcessorsManager.h"
#include "Settings/MainSettings.h"
#include "Utilities/MultiThreading/ProcessingResultProducerConsumer.h"
class ManagerBuilder
{
public:
	ManagerBuilder(const MainSettings& mainSettings, std::shared_ptr<ClientAppContext> pClientAppContext);
	std::unique_ptr<CalculationManager> BuildCalculationManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultBuffer)const;
	std::unique_ptr<InputManager> BuildInputManager()const;
protected:
	std::unique_ptr<VideoSourcesManager> BuildVideoSourcesManager()const;
	std::unique_ptr<ProcessorsManager> BuildProcessorsManager(const std::vector<std::shared_ptr<IVideoSource>>& videoSources,
		const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultBuffer)const;

	const MainSettings& _mainSettings;
	std::shared_ptr<ClientAppContext> _pClientAppContext;
};