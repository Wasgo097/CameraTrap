#pragma once
#include "Utilities/MultiThreading/ThreadsResource.h"
#include "Utilities/MultiThreading/ProcessingResultProducerConsumer.h"
#include "Utilities/ClientAppContext.h"
#include <opencv2/core/mat.hpp>
class CalculationResultManager
{
public:
	CalculationResultManager(const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& processingResultsBuffer,
		ThreadsResourcePtr<cv::Mat> matToGui,
		std::shared_ptr<ClientAppContext> pContext);
	void StartResultsProcessing();
	void StopResultsProcessing();
protected:
	const std::vector<std::shared_ptr<ProcessingResultProducerConsumer>>& _processingResultsBuffer;
	ThreadsResourcePtr<cv::Mat> _matToGui;
	std::shared_ptr<ClientAppContext> _pContext;
	std::unique_ptr<std::jthread> _pProcessingThread;
	std::stop_source _workingThreadStopToken;
	cv::Mat _drawingBuffer;
};