#pragma once
#include "VideoSourcesManager.h"
#include "ProcessorsManager.h"
class CalculationManager
{
public:
	CalculationManager(std::unique_ptr<VideoSourcesManager>&& pVideoSourceManager,
		std::unique_ptr<ProcessorsManager>&& pProcessorsManager) :
		_pVideoSourceManager{ std::move(pVideoSourceManager) },
		_pProcessorsManager{ std::move(pProcessorsManager) }
	{}
	size_t GetVideoSourcesSize()const;
protected:
	std::unique_ptr<VideoSourcesManager> _pVideoSourceManager;
	std::unique_ptr<ProcessorsManager> _pProcessorsManager;
};