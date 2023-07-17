#include "ClientApp.h"
#include "Settings/SettingsBuilder.h"
#include "Manager/ManagerBuilder.h"
#include "Utilities/MatDrawer.h"
//#define STOPWATCH
#ifdef STOPWATCH
#include "Utilities/Stopwatch.h"
#include <iostream>
#endif
const std::string ClientApp::_windowName{"Window"};
ClientApp::ClientApp() :_pContext{ std::make_shared<ClientAppContext>() }, _matToGui{ std::make_shared<cv::Mat>(1, 1, CV_8UC3, cv::Scalar(255, 255, 255)) }
{
	InitMainSettings();
	InitAppContext();
	InitManagers();
}
ClientApp::~ClientApp()
{
	MatDrawer::ClearWindow();
	_pCalculationManager->StopCalculation();
	_pCalculationResultManager->StopWorkingThread();
}
int ClientApp::main()
{
	_pCalculationManager->StartCalculation();
#ifdef STOPWATCH
	Stopwatch loopWatch;
	loopWatch.Start();
#endif
	size_t previousIndexToProcessingResult{ _pContext->drawingIndex };
	while (!_pContext->quit)
	{
		if (_pContext->drawWindow)
		{
			std::shared_lock lock(*_matToGui._pMtx);
			MatDrawer::ShowMat(*_matToGui._pVal, _windowName);
			lock.unlock();
		}
		else
			MatDrawer::ShowMat(_emptyMatToGui, _windowName);
		_pInputManager->ServiceInputFromKeyboard();
#ifdef STOPWATCH
		std::cout << "Loop time: " << loopWatch.ElapsedMilliseconds() << std::endl;
		loopWatch.Reset();
#endif
	}
	return 0;
}

void ClientApp::InitMainSettings()
{
	const std::string mainSettingsDir{ "settings\\" };
	const std::string mainSettingsFile{ "mainsettings.json" };
	SettingsBuilder settingsBuilder(mainSettingsDir);
	_mainSettings = settingsBuilder.GetSettingsFromFile<MainSettings>(mainSettingsFile);
}

void ClientApp::InitManagers()
{
	ManagerBuilder managerBuilder{ _mainSettings,_pContext };
	_pInputManager = managerBuilder.BuildInputManager();
	const auto videoSourcesCount{ _mainSettings.videoSourceSettingsPaths.size() };
	_processingResultsBuffer.reserve(videoSourcesCount);
	for (size_t i{ 0ull }; i < videoSourcesCount; i++)
		_processingResultsBuffer.push_back(std::make_shared<ProcessingResultProducerConsumer>());
	_pCalculationManager = managerBuilder.BuildCalculationManager(_processingResultsBuffer);
	_pCalculationResultManager = managerBuilder.BuildCalculationResultManager(_processingResultsBuffer, _matToGui);
}

void ClientApp::InitAppContext()
{
	_pContext.reset(new ClientAppContext{ .maxDrawingIndex = _mainSettings.videoSourceSettingsPaths.size() });
}