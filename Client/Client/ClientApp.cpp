#include "ClientApp.h"
#include <nlohmann/json.hpp>
#include "Settings/SettingsBuilder.h"
#include "Processor/DebugDrawer.h"
#include "Processor/ProcessorBuilder.h"
#include "Manager/VideoSourcesManagerBuilder.h"
using namespace nlohmann;
ClientApp::ClientApp()
{
	const std::string mainSettingsDir{ "settings\\" };
	const std::string mainSettingsFile{ "mainsettings.json" };
	SettingsBuilder settingsBuilder(mainSettingsDir);
	_mainSettings = settingsBuilder.GetSettingsFromFile<MainSettings>(mainSettingsFile);
	VideoSourcesManagerBuilder videoSourcesManagerBuilder{ _mainSettings.settingsRootDir };
	_pVideoSourceManager = videoSourcesManagerBuilder.BuildVideoSourcesManager(_mainSettings.videoSourceSettingsPaths);
	ProcessorBuilder processorBuilder(_mainSettings.settingsRootDir);
	_diferenceProcessor = processorBuilder.BuildProcessorWithSettings<DifferenceProcessor, DifferenceProcessorSettings, cv::Mat>(_mainSettings.differenceProcessorSettingsPath);
	_moveDetectorProcessor = processorBuilder.BuildProcessorWithSettings<MoveDetectorProcessor, MoveDetectorProcessorSettings, Objects>(_mainSettings.moveDetectorProcessorSettingsPath);
	if (_mainSettings.debugDrawFrames)
	{
		_drawBuffer = std::optional<std::vector<cv::Mat>>{ _pVideoSourceManager->GetVideoSourcesCount() };
	}
}
int ClientApp::main()
{
	auto framesMap = _pVideoSourceManager->GetFramesFromSources();
	int key{ 0 };
	DebugDrawer drawer;
	while (!framesMap.empty())
	{
		size_t drawBufferIndex{ 0 };
		for (const auto& [id, frame] : framesMap)
		{
			if (_mainSettings.debugDrawFrames)
				(*_drawBuffer)[drawBufferIndex] = frame->GetMatCopy();
			_diferenceProcessor->AddNewFrame(frame);
			_diferenceProcessor->Process();
			_moveDetectorProcessor->SetNewDifferenceMat(_diferenceProcessor->GetResult());
			_moveDetectorProcessor->Process();
			if (_mainSettings.debugDrawFrames)
				key = drawer.DrawObjectsAndShowMat((*_drawBuffer)[drawBufferIndex], _moveDetectorProcessor->GetResult(), id);
			else
				key = cv::waitKey(1);
		}
		if (key >= 0)
			break;
		framesMap = _pVideoSourceManager->GetFramesFromSources();
	}
	return 0;
}