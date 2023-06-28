#include "ClientKeyboardController.h"
#include <opencv2/highgui.hpp>
ClientKeyboardController::ClientKeyboardController(std::unordered_map<KeyboardKeys, std::function<void()>>&& keyboardMap) :_keyboardMap{ std::move(keyboardMap) }
{
}

void ClientKeyboardController::CheckKeys()
{
	auto key{ cv::waitKey(1) };
	if (key <= 0)
		return;
	auto keyEnum{ static_cast<KeyboardKeys>(key) };
}
