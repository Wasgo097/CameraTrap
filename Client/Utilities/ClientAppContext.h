#pragma once
struct ClientAppContext
{
	bool quit{ false };
	size_t drawingIndex{ 0 };
	size_t maxDrawingIndex{ 0 };
};