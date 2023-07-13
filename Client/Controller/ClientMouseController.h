#pragma once
#include "MouseButtons.h"
#include <functional>
#include <unordered_map>
class ClientMouseController
{
public:
	ClientMouseController(std::unordered_map<MouseButtons, std::function<void()>>&& mouseMap);
protected:
	std::unordered_map<MouseButtons, std::function<void()>> _mouseMap;
};

