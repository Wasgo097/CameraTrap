#pragma once
#include <memory>
#include "Controller/ClientKeyboardController.h"
#include "Controller/ClientMouseController.h"
class InputManager
{
public:
	InputManager();
	std::unordered_map<KeyboardKeys,std::function<void()>> InitKeyboard();
	std::unordered_map<MouseButtons, std::function<void()>> InitMouse();
protected:
	std::unique_ptr<ClientKeyboardController> _pKeyboard;
	std::unique_ptr<ClientMouseController> _pMouse;
};

