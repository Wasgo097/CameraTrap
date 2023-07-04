#pragma once
#include "KeyboardKeys.h"
#include <functional>
#include <unordered_map>
class ClientKeyboardController
{
public:
	ClientKeyboardController(std::unordered_map<KeyboardKeys, std::function<void()>>&& keyboardMap);
	void Check();
protected:
	std::unordered_map<KeyboardKeys, std::function<void()>> _keyboardMap;
};

