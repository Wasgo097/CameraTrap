#pragma once
#include "ProducerConsumerBase.h"
#include "Interfaces/IObserver.h"
#include "Processor/ProcessorStructs.h"

class ProcessingResultProducerConsumer :public IObserver<MoveDetectionResult>,
	public ProducerConsumerBase<MoveDetectionResult>
{
public:
	void Notify(MoveDetectionResult param) override;
	void ClearDataBuffer();
};