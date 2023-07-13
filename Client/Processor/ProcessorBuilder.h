#pragma once
#include <string>
#include <memory>
#include <concepts>
#include "Settings/SettingsBuilder.h"
#include "Interfaces/IProcessor.h"
class ProcessorBuilder
{
public:
	ProcessorBuilder(std::string processorSettingsRootPath = "");
	template<typename ProcessorType, typename Settings, typename ProcessorResult, typename ProcessorInput>
		requires std::derived_from<ProcessorType, IProcessor<ProcessorResult, ProcessorInput>>
	std::shared_ptr<ProcessorType> BuildProcessorWithSettings(const std::string& path)const
	{
		return std::make_shared<ProcessorType>(_settingsBuilder.GetSettingsFromFile<Settings>(path));
	}

	template<typename ProcessorType, typename ProcessorResult, typename ProcessorInput>
		requires std::derived_from<ProcessorType, IProcessor<ProcessorResult, ProcessorInput>>
	std::shared_ptr<ProcessorType> BuildProcessor()const
	{
		return std::make_shared<ProcessorType>();
	}
protected:
	SettingsBuilder _settingsBuilder;
};