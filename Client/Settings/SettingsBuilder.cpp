#pragma once 
#include "SettingsBuilder.h"
#include <format>
SettingsBuilder::SettingsBuilder(std::string rootDir) :_rootDir{ std::move(rootDir) } 
{
	if (!std::filesystem::exists(_rootDir))
		throw std::invalid_argument(std::format("SettingsBuilder rootDir: {} doesn't exist", _rootDir).c_str());
}
