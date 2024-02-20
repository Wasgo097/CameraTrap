#include "Exporter/SimpleDetectionResultSerializer.h"
#include "Exporter/UdpExporter.h"
#include "Exporter/TcpExporter.h"
#include "Exporter/FileExporter.h"
#include "ExporterBuilder.h"
#include <exception>
std::unique_ptr<IMoveDetectionResultExporter> ExporterBuilder::BuildExporter(const std::string& exporterPath, SerializationType serializationType)
{
	auto serializer{ BuildSerializer(serializationType) };
	std::unique_ptr<IMoveDetectionResultExporter> exporter;
	if (auto udpExporterSettings{ _settingsBuilder.GetSettingsFromFile<UdpExporterSettings>(exporterPath) })
		exporter = std::make_unique<UdpExporter>(*udpExporterSettings, std::move(serializer));
	else if (auto tcpExporterSettings{ _settingsBuilder.GetSettingsFromFile<TcpExporterSettings>(exporterPath) })
		exporter = std::make_unique<TcpExporter>(*tcpExporterSettings, std::move(serializer));
	else if (auto fileExporterSettings{ _settingsBuilder.GetSettingsFromFile<FileExporterSettings>(exporterPath) })
		exporter = std::make_unique<FileExporter>(*fileExporterSettings, std::move(serializer));
	return exporter;
}

std::vector<std::unique_ptr<IMoveDetectionResultExporter>> ExporterBuilder::BuildExporters(const std::vector<std::string>& exporterPaths, SerializationType serializationType)
{
	std::vector<std::unique_ptr<IMoveDetectionResultExporter>> result;
	result.reserve(exporterPaths.size());
	for (const auto& path : exporterPaths)
		result.push_back(BuildExporter(path, serializationType));
	return result;
}

ExporterBuilder::ExporterBuilder(std::string exporterSettingsRootPath) :_settingsBuilder{ std::move(exporterSettingsRootPath) }
{
}

std::unique_ptr<IDetectionResultSerializer> ExporterBuilder::BuildSerializer(SerializationType serializationType)
{
	switch (serializationType)
	{
	case SerializationType::Simple:
		return std::make_unique<SimpleDetectionResultSerializer>();
	case SerializationType::Binary:
		throw std::invalid_argument("Binary serialization isn't current supported");
	default:
		throw std::invalid_argument("Unsupported serialization type");
	}
}