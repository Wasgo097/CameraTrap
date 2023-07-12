#include "CalculationManager.h"
#include <format>
CalculationManager::CalculationManager(std::unique_ptr<VideoSourcesManager>&& pVideoSourceManager,
	std::unique_ptr<ProcessorsManager>&& pProcessorsManager,
	ThreadsResourcePtr<ClientAppContext> pContext) :
	_pVideoSourceManager{ std::move(pVideoSourceManager) },
	_pProcessorsManager{ std::move(pProcessorsManager) },
	_pContext{ std::move(pContext) }
{
}

size_t CalculationManager::GetVideoSourcesSize() const
{
	return _pVideoSourceManager->GetVideoSourcesCount();
}

const cv::Mat& CalculationManager::GetMatFromBuffer() const
{
	std::shared_lock lock(*_pContext._pMtx);
	return _pVideoSourceManager->GetMatFromBuffer(_pContext._pVal->drawingIndex);
}

void CalculationManager::StartCalculation()
{
	_pVideoSourceManager->StartStreaming();
}

void CalculationManager::StopCalculation()
{
	_pVideoSourceManager->StopStreaming();
}
