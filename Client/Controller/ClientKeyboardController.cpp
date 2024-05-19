#include "ClientKeyboardController.h"
#include <opencv2/highgui.hpp>
ClientKeyboardController::ClientKeyboardController(std::unordered_map<KeyboardKeys, std::function<void()>>&& keyboardMap) :_keyboardMap{ std::move(keyboardMap) }
{
}

void ClientKeyboardController::Check()
{
	auto key{ cv::waitKeyEx(1) };
	if (key == -1)
		return;
	auto keyEnum{ static_cast<KeyboardKeys>(key) };
	if (_keyboardMap.contains(keyEnum))
		_keyboardMap[keyEnum]();
}