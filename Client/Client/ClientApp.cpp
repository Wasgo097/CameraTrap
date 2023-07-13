#include "ClientApp.h"
#include "Settings/SettingsBuilder.h"
#include "Manager/ManagerBuilder.h"
#include "Utilities/MatDrawer.h"
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

	ManagerBuilder managerBuilder{ _mainSettings ,_pContext };
	_pInputManager = managerBuilder.BuildInputManager();
	_pCalculationManager = managerBuilder.BuildCalculationManager();
	auto videoSourcesCount{ _pCalculationManager->GetVideoSourcesSize() };
	_pContext._pVal->maxDrawingIndex = videoSourcesCount;
}
int ClientApp::main()
{
	_pCalculationManager->StartCalculation();
#ifdef STOPWATCH
	Stopwatch loopWatch, processingWatch;
	loopWatch.Start();
#endif
	cv::Mat drawingMat;
	while (!_pContext._pVal->quit)
	{
		drawingMat = _pCalculationManager->GetMatFromBuffer().clone();
		if (!drawingMat.empty())
			MatDrawer::ShowMat(drawingMat, "Window");
#ifdef STOPWATCH
		processingWatch.Start();
#endif
		/*for (const auto& [id, frame] : framesMap)
		{
			bool toDraw{ std::stoul(id) == _pContext._pVal->drawingIndex };
			if (toDraw)
				_drawBuffer[_pContext._pVal->drawingIndex] = frame->GetMatCopy();
			const auto& processors{ _processorsPerId[id] };
			processors._pDifferenceProcessor->SetInput(frame);
			processors._pDifferenceProcessor->Process();
			processors._pMoveDetectorProcessor->SetInput(processors._pDifferenceProcessor->GetResult());
			processors._pMoveDetectorProcessor->Process();
			if (toDraw)
				drawer.DrawObjectsAndShowMat(_drawBuffer[_pContext._pVal->drawingIndex], processors._pMoveDetectorProcessor->GetResult().moveDetectionResult, "ClientApp");
		}*/
#ifdef STOPWATCH
		processingWatch.Stop();
#endif
		_pInputManager->ServiceInputFromKeyboard();
#ifdef STOPWATCH
		std::cout << "Loop time: " << loopWatch.ElapsedMilliseconds() << std::endl << "Processing time: " << processingWatch.ElapsedMilliseconds() << std::endl;
		loopWatch.Reset();
#endif
	}
	_pCalculationManager->StopCalculation();
	return 0;
}