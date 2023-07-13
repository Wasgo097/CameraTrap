#include "ProcessingResultProducerConsumer.h"

void ProcessingResultProducerConsumer::Notify(MoveDetectionResult param)
{
	Produce(std::move(param));
}

void ProcessingResultProducerConsumer::ClearDataBuffer()
{
	std::unique_lock<std::mutex> lock(_mtx);
	std::queue<MoveDetectionResult>().swap(_dataQueue);
}
