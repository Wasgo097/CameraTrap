#pragma once
#include "Interfaces/IDetectionResultSerializer.h"
#include "Interfaces/IMoveDetectionResultExporter.h"
#include "Utilities/SerializationHelper.h"
#include "Settings/SettingsBuilder.h"
#include <memory>
class ExporterBuilder
{
public:
	ExporterBuilder(std::string exporterSettingsRootPath);
	std::unique_ptr<IMoveDetectionResultExporter> BuildExporter(const std::string& exporterPath, SerializationType serializationType);
protected:
	std::unique_ptr<IDetectionResultSerializer> BuildSerializer(SerializationType serializationType);
	const SettingsBuilder _settingsBuilder;
};