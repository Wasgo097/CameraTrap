#include <Windows.h>
#include "Window.h"
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCMDLIne, int nCmdShow)
{
	Window window{ 600,300,"WindowName" };
	MSG msg;
	BOOL msgResult;
	while ((msgResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msgResult == -1)
		return -1;
	return msg.wParam;
}