#pragma once
#include <functional>
#include <unordered_map>
#include "MouseButtons.h"
class ClientMouseController
{
public:
	ClientMouseController(std::unordered_map<MouseButtons, std::function<void()>>&& mouseMap);
protected:
	std::unordered_map<MouseButtons, std::function<void()>> _mouseMap;
};

