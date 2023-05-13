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
	ProcessorBuilder(std::string processorSettingsRootPath);
	template<typename T, typename S, typename ProcessorType>
		requires std::derived_from<T, IProcessor<ProcessorType>>
	std::shared_ptr<T> BuildSimpleProcessor(const std::string& path)const
	{
		return std::make_shared<T>(_settingsBuilder.GetSettingsFromFile<S>(path));
	}
protected:
	SettingsBuilder _settingsBuilder;
};