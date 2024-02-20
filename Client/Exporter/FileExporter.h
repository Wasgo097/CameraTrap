#pragma once
#include "Interfaces/IDetectionResultSerializer.h"
#include "Interfaces/IMoveDetectionResultExporter.h"
#include "Settings/FileExporterSettings.h"
#include <fstream>
#include <memory>
class FileExporter :public IMoveDetectionResultExporter
{
public:
	FileExporter(FileExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer);
	void ExportData(const MoveDetectionResult& dataToExport) override;
protected:
	FileExporterSettings _settings;
	std::string _serializationBuffer;
	std::unique_ptr<IDetectionResultSerializer> _pSerializer;
};