#include "FileExporter.h"

FileExporter::FileExporter(FileExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer) :
	_settings{ std::move(settings) },
	_pSerializer{ std::move(pSerializer) }
{
}

void FileExporter::ExportData(const MoveDetectionResult& dataToExport)
{
}
