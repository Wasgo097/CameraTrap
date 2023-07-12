#pragma once
#include "Settings/MainSettings.h"
#include "Manager/CalculationManager.h"
#include "Manager/InputManager.h"

class ClientApp
{
public:
	ClientApp();
	int main();
protected:
	MainSettings _mainSettings;
	std::unique_ptr<InputManager> _pInputManager;
	std::unique_ptr<CalculationManager> _pCalculationManager;
	ThreadsResourcePtr<ClientAppContext> _pContext;
};