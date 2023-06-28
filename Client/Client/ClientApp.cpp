#include "ClientApp.h"
#include "Settings/SettingsBuilder.h"
#include "Processor/ProcessorBuilder.h"
#include "Manager/VideoSourcesManagerBuilder.h"
#include "Utilities/DebugDrawer.h"
//#define STOPWATCH
#ifdef STOPWATCH
#include "Utilities/Stopwatch.h"
#endif
ClientApp::ClientApp() :_pContext{ std::make_shared<ClientAppContext>() }
{
	const std::string mainSettingsDir{ "settings\\" };
	const std::string mainSettingsFile{ "mainsettings.json" };

	SettingsBuilder settingsBuilder(mainSettingsDir);
	_mainSettings = settingsBuilder.GetSettingsFromFile<MainSettings>(mainSettingsFile);

	VideoSourcesManagerBuilder videoSourcesManagerBuilder{ _mainSettings.settingsRootDir };
	_pVideoSourceManager = videoSourcesManagerBuilder.BuildVideoSourcesManager(_mainSettings.videoSourceSettingsPaths);

	_pInputManager = std::make_unique<InputManager>(_pContext);

	ProcessorBuilder processorBuilder(_mainSettings.settingsRootDir);
	_pDiferenceProcessor = processorBuilder.BuildProcessorWithSettings<DifferenceProcessor, DifferenceProcessorSettings, cv::Mat>(_mainSettings.differenceProcessorSettingsPath);
	_pMoveDetectorProcessor = processorBuilder.BuildProcessorWithSettings<MoveDetectorProcessor, MoveDetectorProcessorSettings, Objects>(_mainSettings.moveDetectorProcessorSettingsPath);

	auto videoSourcesCount{ _pVideoSourceManager->GetVideoSourcesCount() };
	_drawBuffer = std::vector<cv::Mat>{ videoSourcesCount };
	_pContext->maxDrawingIndex = videoSourcesCount;
}
int ClientApp::main()
{
	auto framesMap = _pVideoSourceManager->GetFramesFromSources();
	DebugDrawer drawer;
#ifdef STOPWATCH
	Stopwatch watch;
	watch.Start();
#endif
	while (!_pContext->quit)
	{
		for (const auto& [id, frame] : framesMap)
		{
			bool toDraw{ std::stoul(id) == _pContext->drawingIndex };
			if (toDraw)
				_drawBuffer[_pContext->drawingIndex] = frame->GetMatCopy();

			_pDiferenceProcessor->AddNewFrame(frame);
			_pDiferenceProcessor->Process();
			_pMoveDetectorProcessor->SetNewDifferenceMat(_pDiferenceProcessor->GetResult());
			_pMoveDetectorProcessor->Process();
		}
		framesMap = _pVideoSourceManager->GetFramesFromSources();
#ifdef STOPWATCH
		std::cout << "Loop time: " << watch.ElapsedMilliseconds() << std::endl;
		watch.Reset();
#endif
		drawer.DrawObjectsAndShowMat(_drawBuffer[_pContext->drawingIndex], _pMoveDetectorProcessor->GetResult(), "ClientApp");
		_pInputManager->ServiceInputFromKeyboard();
		}
	return 0;
	}