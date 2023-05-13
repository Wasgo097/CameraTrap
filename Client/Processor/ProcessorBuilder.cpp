#include "ProcessorBuilder.h"
#include <filesystem>
#include <fstream>
#include <format>
ProcessorBuilder::ProcessorBuilder(std::string processorSettingsRootPath) :_settingsBuilder{ std::move(processorSettingsRootPath) }
{}
