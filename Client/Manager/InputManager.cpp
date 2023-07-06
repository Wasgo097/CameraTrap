#include "InputManager.h"
#include "Controller/ClientMouseController.h"
#include "Controller/ClientKeyboardController.h"
#include <algorithm>
InputManager::InputManager(ThreadsResourcePtr<ClientAppContext> clientAppContext) :
	_pClientAppContext{ std::move(clientAppContext) },
	_pKeyboard{ std::make_unique<ClientKeyboardController>(InitKeyboard()) },
	_pMouse{ std::make_unique<ClientMouseController>(InitMouse()) }
{
}

void InputManager::ServiceInputFromKeyboard()
{
	_pKeyboard->Check();
}

std::unordered_map<KeyboardKeys, std::function<void()>> InputManager::InitKeyboard()
{
	std::unordered_map<KeyboardKeys, std::function<void()>> result;
	result[KeyboardKeys::Q] = [this]()
	{
		std::unique_lock lock(*_pClientAppContext._pMtx);
		_pClientAppContext._pVal->quit = true;
	};
	result[KeyboardKeys::Left] = [this]()
	{
		std::unique_lock lock(*_pClientAppContext._pMtx);
		auto& drawingIndex{ _pClientAppContext._pVal->drawingIndex };
		drawingIndex--;
		drawingIndex = std::clamp(drawingIndex, 0ull, _pClientAppContext._pVal->maxDrawingIndex - 1);
	};
	result[KeyboardKeys::Right] = [this]()
	{
		std::unique_lock lock(*_pClientAppContext._pMtx);
		auto& drawingIndex{ _pClientAppContext._pVal->drawingIndex };
		drawingIndex++;
		if (drawingIndex == _pClientAppContext._pVal->maxDrawingIndex)
			drawingIndex = 0;
	};
	return result;
}

std::unordered_map<MouseButtons, std::function<void()>> InputManager::InitMouse()
{
	return {};
}
