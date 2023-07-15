#include "InputManager.h"
#include "Controller/ClientMouseController.h"
#include "Controller/ClientKeyboardController.h"
#include <algorithm>
InputManager::InputManager(std::shared_ptr<ClientAppContext> clientAppContext) :
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
		_pClientAppContext->quit = true;
	};
	result[KeyboardKeys::V] = [this]()
	{
		_pClientAppContext->drawWindow = !_pClientAppContext->drawWindow;
	};
	result[KeyboardKeys::Left] = [this]()
	{
		auto& drawingIndex{ _pClientAppContext->drawingIndex };
		drawingIndex--;
		drawingIndex = std::clamp(drawingIndex, 0ull, _pClientAppContext->maxDrawingIndex - 1);
	};
	result[KeyboardKeys::Right] = [this]()
	{
		auto& drawingIndex{ _pClientAppContext->drawingIndex };
		drawingIndex++;
		if (drawingIndex == _pClientAppContext->maxDrawingIndex)
			drawingIndex = 0;
	};
	return result;
}

std::unordered_map<MouseButtons, std::function<void()>> InputManager::InitMouse()
{
	return {};
}
