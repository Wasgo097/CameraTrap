#include "ManagerBuilder.h"
#include "VideoSource/VideoSourceBuilder.h"
ManagerBuilder::ManagerBuilder(const MainSettings& mainSettings, ThreadsResourcePtr<ClientAppContext> pClientAppContext) :
	_mainSettings{ mainSettings },
	_pClientAppContext{ std::move(pClientAppContext) }
{}

std::unique_ptr<CalculationManager> ManagerBuilder::BuildCalculationManager() const
{
	return {};
}

std::unique_ptr<VideoSourcesManager> ManagerBuilder::BuildVideoSourcesManager() const
{
	VideoSourceBuilder videoSourceBuilder(_mainSettings.settingsRootDir);
	return std::make_unique<VideoSourcesManager>(videoSourceBuilder.BuildVideoSources(_mainSettings.videoSourceSettingsPaths));
}

std::unique_ptr<InputManager> ManagerBuilder::BuildInputManager() const
{
	return std::make_unique<InputManager>(_pClientAppContext);
}