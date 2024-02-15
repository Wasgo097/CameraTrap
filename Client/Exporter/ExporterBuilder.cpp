#include "Exporter/SimpleDetectionResultSerializer.h"
#include "Exporter/UdpExporter.h"
#include "Exporter/TcpExporter.h"
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
	return exporter;
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
		throw std::invalid_argument("Binary serialization isn't current available");
	default:
		throw std::invalid_argument("Unsupported serialization type");
	}
}
