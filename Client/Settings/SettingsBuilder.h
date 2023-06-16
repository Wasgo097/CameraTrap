#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include "CameraVideoSourceSettings.h"
#include "DifferenceProcessorSettings.h"
#include "FileVideoSourceSettings.h"
#include "MainSettings.h"
#include "MoveDetectorProcessorSettings.h"
class SettingsBuilder
{
public:
	SettingsBuilder(std::string rootDir = "");
	template<typename T>
	T GetSettingsFromFile(const std::string& path)const {
		const std::string finalPath = _rootDir + path;
		if (!std::filesystem::exists(finalPath))
			throw std::invalid_argument{ std::format("Final path: {} in SettingsBuilder::GetSettingsFromFile doesn't exist",finalPath).c_str() };
		std::ifstream str(finalPath);
		T settings;
		nlohmann::json jfile;
		str >> jfile;
		str.close();
		settings = jfile;
		return settings;
	}
	template<typename T>
	bool CreateFileWithSettings(const std::string& path, const T& settings)const {
		const std::string finalPath = _rootDir + path;
		std::ofstream str(finalPath);
		nlohmann::json jfile = settings;
		str << jfile.dump(4);
		str.close();
		return true;
	}
protected:
	const std::string _rootDir;
};