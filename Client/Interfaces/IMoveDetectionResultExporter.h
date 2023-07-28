#pragma once
#include "Processor/ProcessorStructs.h"
class IMoveDetectionResultExporter
{
public:
	virtual ~IMoveDetectionResultExporter() = default;
	virtual bool ExportData(const MoveDetectionResult& dataToExport) = 0;
};