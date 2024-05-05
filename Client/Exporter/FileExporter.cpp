#include "FileExporter.h"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <filesystem>
namespace fs = std::filesystem;
FileExporter::FileExporter(FileExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer) :
	_settings{ std::move(settings) },
	_pSerializer{ std::move(pSerializer) }
{
	if (!fs::exists(_settings.outputDirectory))
		fs::create_directory(_settings.outputDirectory);
}

void FileExporter::ExportData(const MoveDetectionResult& dataToExport)
{
	auto currTimeBase = std::format("{}\\{}", _settings.outputDirectory, GetLocalTime());
	_serializationBuffer = std::move(_pSerializer->Serialize(dataToExport));
	std::ofstream file(currTimeBase + ".log");
	if (file.is_open())
	{
		file << _serializationBuffer;
		file.close();
	}
	cv::imwrite(currTimeBase + ".jpg", dataToExport.pRawFrame->GetMatCRef());
}

std::string FileExporter::GetLocalTime()
{
	// Get the current time point
	auto currentTime = std::chrono::system_clock::now();
	// Convert the current time point to a time_t object
	std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
	// Convert the time_t object to a local time
	std::tm localTime = *std::localtime(&currentTimeT);
	// Get milliseconds
	auto duration = currentTime.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
	// Convert the local time to a string
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y_%m_%d__%H-%M-%S") << "-" << std::setfill('0') << std::setw(3) << millis.count();
	return oss.str();
}