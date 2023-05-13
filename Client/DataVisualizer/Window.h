#pragma once
#include <memory>
class Window
{
public:
	Window(int width, int height, const char* windowName);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	struct Impl;
	std::unique_ptr<Impl> _pImpl;
};
