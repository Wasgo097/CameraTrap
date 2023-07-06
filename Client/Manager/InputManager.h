#pragma once
#include "Controller/ClientKeyboardController.h"
#include "Controller/ClientMouseController.h"
#include "Utilities/ClientAppContext.h"
#include "Utilities/ThreadsResource.h"
class InputManager
{
public:
	InputManager(ThreadsResourcePtr<ClientAppContext> pClientAppContext);
	void ServiceInputFromKeyboard();
protected:
	std::unordered_map<KeyboardKeys, std::function<void()>> InitKeyboard();
	std::unordered_map<MouseButtons, std::function<void()>> InitMouse();
	std::unique_ptr<ClientKeyboardController> _pKeyboard;
	std::unique_ptr<ClientMouseController> _pMouse;
	ThreadsResourcePtr<ClientAppContext> _pClientAppContext;
};

