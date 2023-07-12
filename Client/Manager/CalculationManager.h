#pragma once
#include "VideoSourcesManager.h"
#include "ProcessorsManager.h"
class CalculationManager
{
public:
	CalculationManager(std::unique_ptr<VideoSourcesManager>&& pVideoSourceManager,
		std::unique_ptr<ProcessorsManager>&& pProcessorsManager, 
		ThreadsResourcePtr<ClientAppContext> pContext);
	size_t GetVideoSourcesSize() const;
	const cv::Mat& GetMatFromBuffer() const;
	void StartCalculation();
	void StopCalculation();
protected:
	std::unique_ptr<VideoSourcesManager> _pVideoSourceManager;
	std::unique_ptr<ProcessorsManager> _pProcessorsManager;
	ThreadsResourcePtr<ClientAppContext> _pContext;
};