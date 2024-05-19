#include "ProcessingResultProducerConsumer.h"

void ProcessingResultProducerConsumer::Notify(MoveDetectionResult param)
{
	Produce(std::move(param));
}