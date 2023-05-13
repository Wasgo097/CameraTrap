#pragma warning(disable : 4996)
#include "pch.h"
#include "Window.h"
#include <string>

Window::Window(int width, int height, const char* windowName) :
	_pImpl{ std::make_unique<Impl>(width,height,windowName) }
{
}

Window::~Window() = default;

struct Window::Impl
{
	Impl(int width, int height, const char* windowName) :
		width{ width }, height{ height }, hInstance{ GetModuleHandle(nullptr) }
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = windowClassName;
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);

		const size_t cSize = strlen(windowName) + 1;
		std::wstring tempWndName(cSize, L'\0');
		mbstowcs(tempWndName.data(), windowName, cSize);
		this->windowName = std::move(tempWndName);

		RECT wr;
		wr.left = 100;
		wr.right = width + wr.left;
		wr.top = 100;
		wr.bottom = height + wr.top;
		AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
		hWindow = CreateWindow(
			windowClassName, this->windowName.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
			nullptr, nullptr, hInstance, this
		);
		ShowWindow(hWindow, SW_SHOWDEFAULT);
	}

	~Impl()
	{
		DestroyWindow(hWindow);
		UnregisterClass(windowClassName, hInstance);
	}

	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		if (msg == WM_NCCREATE)
		{
			const auto pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			const auto pInstance = static_cast<Impl*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pInstance));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&HandleMsgStatic));
			return pInstance->HandleMsg(hWnd, msg, wParam, lParam);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	static LRESULT CALLBACK HandleMsgStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		const auto pInstance = reinterpret_cast<Impl*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pInstance->HandleMsg(hWnd, msg, wParam, lParam);
	}
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	int width;
	int height;
	std::wstring windowName;
	HWND hWindow;
	static constexpr auto windowClassName{ L"WindowClassName" };
	HINSTANCE hInstance;
};