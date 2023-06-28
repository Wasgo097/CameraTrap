#pragma once
#include <functional>
#include <unordered_map>
#include "KeyboardKeys.h"
class ClientKeyboardController
{
public:
	ClientKeyboardController(std::unordered_map<KeyboardKeys, std::function<void()>>&& keyboardMap);
	void CheckKeys();
protected:
	std::unordered_map<KeyboardKeys, std::function<void()>> _keyboardMap;
};

