#pragma once
#include <atomic>
struct ClientAppContext
{
	std::atomic_bool quit{ false };
	std::atomic_bool drawWindow{ true };
	std::atomic_size_t drawingIndex{ 0 };
	const size_t maxDrawingIndex{ 0 };
};