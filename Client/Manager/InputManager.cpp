#include "InputManager.h"
#include "Controller/ClientMouseController.h"
#include "Controller/ClientKeyboardController.h"

InputManager::InputManager() :_pKeyboard{ std::make_unique<ClientKeyboardController>(InitKeyboard()) }, _pMouse{ std::make_unique<ClientMouseController>(InitMouse()) }
{
}

std::unordered_map<KeyboardKeys, std::function<void()>> InputManager::InitKeyboard()
{
	std::unordered_map<KeyboardKeys, std::function<void()>> result;
	return result;
}

std::unordered_map<MouseButtons, std::function<void()>> InputManager::InitMouse()
{
	return {};
}
