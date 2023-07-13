#pragma once
#include "Settings/MainSettings.h"
#include "Manager/CalculationManager.h"
#include "Manager/InputManager.h"
#include "Utilities/MultiThreading/ProcessingResultProducerConsumer.h"
class ClientApp
{
public:
	ClientApp();
	int main();
protected:
	void InitMainSettings();
	void InitManagers();
	void InitAppContext();
	MainSettings _mainSettings;
	std::unique_ptr<InputManager> _pInputManager;
	std::unique_ptr<CalculationManager> _pCalculationManager;
	std::shared_ptr<ClientAppContext> _pContext;
	std::vector<std::shared_ptr<ProcessingResultProducerConsumer>> _processingResultsBuffer;
};