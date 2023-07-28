#pragma once
#include "Interfaces/IMoveDetectionResultExporter.h"
class UdpExporter :public IMoveDetectionResultExporter
{
public:
	// Inherited via IMoveDetectionResultExporter
	virtual bool ExportData(const MoveDetectionResult& dataToExport) override;
};