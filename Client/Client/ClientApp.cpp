#include "ClientApp.h"
#include "Settings/SettingsBuilder.h"
#include "Processor/ProcessorBuilder.h"
#include "Processor/DifferenceProcessor.h"
#include "Processor/MoveDetectorProcessor.h"
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

	auto videoSourcesIds{ _pVideoSourceManager->GetVideoSourcesIds() };
	for (const auto& id : videoSourcesIds)
	{
		_processorsPerId[id]._pDifferenceProcessor = processorBuilder.BuildProcessorWithSettings<DifferenceProcessor, DifferenceProcessorSettings, DifferenceResult, std::shared_ptr<IFrame>>(_mainSettings.differenceProcessorSettingsPath);
		_processorsPerId[id]._pMoveDetectorProcessor = processorBuilder.BuildProcessorWithSettings<MoveDetectorProcessor, MoveDetectorProcessorSettings, MoveDetectionResult, DifferenceResult>(_mainSettings.moveDetectorProcessorSettingsPath);
	}

	auto videoSourcesCount{ _pVideoSourceManager->GetVideoSourcesCount() };
	_drawBuffer = std::vector<cv::Mat>{ videoSourcesCount };
	_pContext->maxDrawingIndex = videoSourcesCount;
}
int ClientApp::main()
{
	auto framesMap = _pVideoSourceManager->GetFramesFromSources();
	DebugDrawer drawer;
#ifdef STOPWATCH
	Stopwatch loopWatch, processingWatch;
	loopWatch.Start();
#endif
	while (!_pContext->quit)
	{
#ifdef STOPWATCH
		processingWatch.Start();
#endif
		for (const auto& [id, frame] : framesMap)
		{
			bool toDraw{ std::stoul(id) == _pContext->drawingIndex };
			if (toDraw)
				_drawBuffer[_pContext->drawingIndex] = frame->GetMatCopy();
			const auto& processors{ _processorsPerId[id] };
			processors._pDifferenceProcessor->SetInput(frame);
			processors._pDifferenceProcessor->Process();
			processors._pMoveDetectorProcessor->SetInput(processors._pDifferenceProcessor->GetResult());
			processors._pMoveDetectorProcessor->Process();
			if (toDraw)
				drawer.DrawObjectsAndShowMat(_drawBuffer[_pContext->drawingIndex], processors._pMoveDetectorProcessor->GetResult().movingObjects, "ClientApp");
		}
#ifdef STOPWATCH
		processingWatch.Stop();
#endif
		_pInputManager->ServiceInputFromKeyboard();
		framesMap = _pVideoSourceManager->GetFramesFromSources();
#ifdef STOPWATCH
		std::cout << "Loop time: " << loopWatch.ElapsedMilliseconds() << std::endl << "Processing time: " << processingWatch.ElapsedMilliseconds() << std::endl;
		loopWatch.Reset();
#endif
	}
	return 0;
}