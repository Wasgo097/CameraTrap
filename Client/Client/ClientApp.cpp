#include "ClientApp.h"
#include "Settings/SettingsBuilder.h"
#include "Processor/DebugDrawer.h"
#include "Processor/ProcessorBuilder.h"
#include "Manager/VideoSourcesManagerBuilder.h"
#include "Utilities/Stopwatch.h"
#include <nlohmann/json.hpp>
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
	_pDiferenceProcessor = processorBuilder.BuildProcessorWithSettings<DifferenceProcessor, DifferenceProcessorSettings, cv::Mat>(_mainSettings.differenceProcessorSettingsPath);
	_pMoveDetectorProcessor = processorBuilder.BuildProcessorWithSettings<MoveDetectorProcessor, MoveDetectorProcessorSettings, Objects>(_mainSettings.moveDetectorProcessorSettingsPath);
	if (_mainSettings.debugDrawFrames)
		_drawBuffer = std::vector<cv::Mat>{ _pVideoSourceManager->GetVideoSourcesCount() };
}
int ClientApp::main()
{
	auto framesMap = _pVideoSourceManager->GetFramesFromSources();
	int key{ 0 };
	DebugDrawer drawer;
	Stopwatch watch;
	watch.Start();
	while (!framesMap.empty())
	{
		size_t drawBufferIndex{ 0 };
		for (const auto& [id, frame] : framesMap)
		{
			if (_mainSettings.debugDrawFrames)
				_drawBuffer[drawBufferIndex] = frame->GetMatCopy();
			_pDiferenceProcessor->AddNewFrame(frame);
			_pDiferenceProcessor->Process();
			_pMoveDetectorProcessor->SetNewDifferenceMat(_pDiferenceProcessor->GetResult());
			_pMoveDetectorProcessor->Process();
			if (_mainSettings.debugDrawFrames)
				key = drawer.DrawObjectsAndShowMat(_drawBuffer[drawBufferIndex], _pMoveDetectorProcessor->GetResult(), id);
			else
				key = cv::waitKey(1);
			drawBufferIndex++;
		}
		if (key >= 0)
			break;
		framesMap = _pVideoSourceManager->GetFramesFromSources();
		std::cout << "Loop time: " << watch.ElapsedMilliseconds() << std::endl;
		watch.Reset();
	}
	return 0;
}