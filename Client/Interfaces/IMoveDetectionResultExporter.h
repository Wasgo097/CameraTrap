#pragma once
#include "Processor/ProcessorStructs.h"
class IMoveDetectionResultExporter
{
public:
	virtual ~IMoveDetectionResultExporter() = default;
	virtual void ExportData(const MoveDetectionResult& dataToExport) = 0;
};