#include "CalculationManager.h"
#include <format>
CalculationManager::CalculationManager(std::unique_ptr<VideoSourcesManager>&& pVideoSourceManager,
	std::unique_ptr<ProcessorsManager>&& pProcessorsManager) :
	_pVideoSourceManager{ std::move(pVideoSourceManager) },
	_pProcessorsManager{ std::move(pProcessorsManager) }
{
}

void CalculationManager::StartCalculation()
{
	_pVideoSourceManager->StartStreaming();
}

void CalculationManager::StopCalculation()
{
	_pVideoSourceManager->StopStreaming();
}
