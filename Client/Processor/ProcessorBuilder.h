#pragma once
#include <string>
#include <memory>
#include <concepts>
#include "Settings/SettingsBuilder.h"
#include "DifferenceProcessor.h"
#include "Interfaces/IProcessor.h"
class ProcessorBuilder
{
public:
	ProcessorBuilder(std::string processorSettingsRootPath = "");
	template<typename ProcessorType, typename Settings, typename ProcessorResult>
		requires std::derived_from<ProcessorType, IProcessor<ProcessorResult>>
	std::shared_ptr<ProcessorType> BuildProcessorWithSettings(const std::string& path)const
	{
		return std::make_shared<ProcessorType>(_settingsBuilder.GetSettingsFromFile<Settings>(path));
	}
	template<typename ProcessorType, typename Param, typename ProcessorResult>
		requires std::derived_from<ProcessorType, IProcessor<ProcessorResult>>
	std::shared_ptr<ProcessorType> BuildProcessorWithParam(Param&& param)const
	{
		return std::make_shared<ProcessorType>(std::move(param));
	}
	template<typename ProcessorType, typename ProcessorResult>
		requires std::derived_from<ProcessorType, IProcessor<ProcessorResult>>
	std::shared_ptr<ProcessorType> BuildProcessor()const
	{
		return std::make_shared<ProcessorType>();
	}
protected:
	SettingsBuilder _settingsBuilder;
};