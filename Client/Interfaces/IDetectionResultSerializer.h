#pragma once
#include "Processor/ProcessorStructs.h"
#include "Utilities/SerializationHelper.h"
#include <string>
class IDetectionResultSerializer
{
public:
	virtual ~IDetectionResultSerializer() = default;
	virtual std::string Serialize(const MoveDetectionResult& detectionResult) = 0;
	virtual SerializationType GetSerializationType()const = 0;
};