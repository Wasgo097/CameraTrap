#pragma once
#include "VideoSourcesManager.h"
#include "InputManager.h"
#include "CalculationManager.h"
#include "Settings/MainSettings.h"
class ManagerBuilder
{
public:
	ManagerBuilder(const MainSettings& mainSettings, ThreadsResourcePtr<ClientAppContext> pClientAppContext);
	std::unique_ptr<CalculationManager> BuildCalculationManager()const;
	std::unique_ptr<InputManager> BuildInputManager()const;
protected:
	std::unique_ptr<VideoSourcesManager> BuildVideoSourcesManager()const;
	const MainSettings& _mainSettings;
	ThreadsResourcePtr<ClientAppContext> _pClientAppContext;
};