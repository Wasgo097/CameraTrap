#include "CalculationResultManager.h"
#include "Utilities/MatDrawer.h"
//#define STOPWATCH
#ifdef STOPWATCH
#include "Utilities/Stopwatch.h"
#include <iostream>
#endif
#include <future>
CalculationResultManager::CalculationResultManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultsBuffer,
	ThreadsResourcePtr<cv::Mat> matToGui,
	std::shared_ptr<ClientAppContext> pContext) :
	_processingResultsBuffer{ processingResultsBuffer },
	_matToGui{ std::move(matToGui) },
	_pContext{ pContext }
{
}

void CalculationResultManager::StartResultsProcessing()
{
	_pProcessingThread = std::make_unique<std::jthread>(
		[this](const std::stop_token& stopToken)
		{
			std::vector<std::future<MoveDetectionResult>> asyncResultsFromProducers;
#ifdef STOPWATCH
			Stopwatch watch;
			watch.Start();
#endif
			while (!stopToken.stop_requested())
			{
				for (const auto& processingResultBuffer : _processingResultsBuffer)
				{
					asyncResultsFromProducers.push_back(std::async(std::launch::async | std::launch::deferred, &ProcessingResultProducerConsumer::ConsumeNewest, processingResultBuffer.get()));
					processingResultBuffer->ClearDataBuffer();
				}
				for (size_t index{ 0ull }; index < asyncResultsFromProducers.size(); index++)
				{
					auto result{ asyncResultsFromProducers[index].get() };
					if (_pContext->drawWindow and index == _pContext->drawingIndex)
					{
						std::unique_lock lock(*_matToGui._pMtx);
						*_matToGui._pVal = result.pRawFrame->GetMatCRef().clone();
						MatDrawer::DrawObjectsOnMat(*_matToGui._pVal, result.moveDetectionResult);
						lock.unlock();
					}
				}
				asyncResultsFromProducers.clear();
#ifdef STOPWATCH
				std::cout << "Processing time loop: " << watch.ElapsedMilliseconds() << std::endl;
				watch.Reset();
#endif
					}
				}, _workingThreadStopToken.get_token());
			}

void CalculationResultManager::StopResultsProcessing()
{
	_workingThreadStopToken.request_stop();
	if (_pProcessingThread->joinable())
		_pProcessingThread->join();
	_pProcessingThread.reset();
}