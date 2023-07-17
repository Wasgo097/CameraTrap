#include "CalculationResultManager.h"
#include "Utilities/MatDrawer.h"
#include <future>
CalculationResultManager::CalculationResultManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultsBuffer,
	ThreadsResourcePtr<cv::Mat> matToGui,
	std::shared_ptr<ClientAppContext> pContext) :
	_processingResultsBuffer{ processingResultsBuffer },
	_matToGui{ std::move(matToGui) },
	_pContext{ pContext }
{
	_pProcessingThread = std::make_unique<std::jthread>(&CalculationResultManager::WorkingThread, this, _workingThreadStopToken.get_token());
}

void CalculationResultManager::WorkingThread(const std::stop_token& stopToken)
{
	std::vector<std::future<MoveDetectionResult>> asyncResultsFromProducers;
	while (!stopToken.stop_requested())
	{
		for (const auto& processingResult : _processingResultsBuffer)
			asyncResultsFromProducers.emplace_back(std::async(std::launch::async | std::launch::deferred, &ProcessingResultProducerConsumer::Consume, processingResult.get()));
		for (size_t index{ 0ull }; index < asyncResultsFromProducers.size(); index++)
		{
			auto result{ asyncResultsFromProducers[index].get() };
			if (index == _pContext->drawingIndex)
			{
				std::unique_lock lock(*_matToGui._pMtx);
				*_matToGui._pVal = result.pRawFrame->GetMatCRef().clone();
				MatDrawer::DrawObjectsOnMat(*_matToGui._pVal, result.moveDetectionResult);
				lock.unlock();
			}
		}
		asyncResultsFromProducers.clear();
	}
}

void CalculationResultManager::StopWorkingThread()
{
	for (const auto& processingResult : _processingResultsBuffer)
		processingResult->ClearDataBuffer();
	_workingThreadStopToken.request_stop();
	if (_pProcessingThread->joinable())
		_pProcessingThread->join();
	_pProcessingThread.reset();
}