#pragma once
struct ClientAppContext
{
	bool quit{ false };
	bool drawWindow{ true };
	size_t drawingIndex{ 0 };
	const size_t maxDrawingIndex{ 0 };
};