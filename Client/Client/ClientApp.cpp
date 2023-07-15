#include "ClientApp.h"
#include "Settings/SettingsBuilder.h"
#include "Manager/ManagerBuilder.h"
#include "Utilities/MatDrawer.h"
#define STOPWATCH
#ifdef STOPWATCH
#include "Utilities/Stopwatch.h"
#include <iostream>
#endif
const std::string ClientApp::_windowName{"Window"};
ClientApp::ClientApp() :_pContext{ std::make_shared<ClientAppContext>() }
{
	InitMainSettings();
	InitAppContext();
	InitManagers();
}
ClientApp::~ClientApp()
{
	MatDrawer::ClearWindow();
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
		auto& currentProcessingResultBuffer{ _processingResultsBuffer[_pContext->drawingIndex] };
		if (previousIndexToProcessingResult != _pContext->drawingIndex)
		{
			currentProcessingResultBuffer->ClearDataBuffer();
			previousIndexToProcessingResult = _pContext->drawingIndex;
		}
		if (_pContext->drawWindow)
		{
			auto moveDetectionResult{ currentProcessingResultBuffer->Consume() };
			if (_matToGui = moveDetectionResult.rawFrame->GetMatCopy(); !_matToGui.empty())
			{
				MatDrawer::DrawObjectsOnMat(_matToGui, moveDetectionResult.moveDetectionResult);
				MatDrawer::ShowMat(_matToGui, _windowName);
			}
		}
		else
			MatDrawer::ShowMat(_emptyMatToGui, _windowName);
		_pInputManager->ServiceInputFromKeyboard();
#ifdef STOPWATCH
		std::cout << "Loop time: " << loopWatch.ElapsedMilliseconds() << std::endl;
		loopWatch.Reset();
#endif
	}
	_pCalculationManager->StopCalculation();
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
}

void ClientApp::InitAppContext()
{
	_pContext.reset(new ClientAppContext{ .maxDrawingIndex = _mainSettings.videoSourceSettingsPaths.size() });
}