#include "InputManager.h"
#include "Controller/ClientMouseController.h"
#include "Controller/ClientKeyboardController.h"
#include <algorithm>
InputManager::InputManager(std::shared_ptr<ClientAppContext> pContext) :
	_pContext{ std::move(pContext) },
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
		_pContext->quit = true;
	};
	result[KeyboardKeys::V] = [this]()
	{
		_pContext->drawWindow = !_pContext->drawWindow;
	};
	result[KeyboardKeys::Left] = [this]()
	{
		auto drawingIndex{ _pContext->drawingIndex.load() };
		drawingIndex--;
		drawingIndex = std::clamp(drawingIndex, 0ull, _pContext->maxDrawingIndex - 1);
		_pContext->drawingIndex = drawingIndex;
	};
	result[KeyboardKeys::Right] = [this]()
	{
		auto drawingIndex{ _pContext->drawingIndex.load() };
		drawingIndex++;
		if (drawingIndex == _pContext->maxDrawingIndex)
			drawingIndex = 0;
		_pContext->drawingIndex = drawingIndex;
	};
	return result;
}

std::unordered_map<MouseButtons, std::function<void()>> InputManager::InitMouse()
{
	return {};
}
