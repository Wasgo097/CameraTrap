#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
class SettingsBuilder
{
public:
	SettingsBuilder(std::string rootDir = "");
	template<typename T>
	std::optional<T> GetSettingsFromFile(const std::string& path)const
	{
		const std::string finalPath = _rootDir + path;
		if (!std::filesystem::exists(finalPath))
			throw std::invalid_argument{ std::format("Final path: {} in SettingsBuilder::GetSettingsFromFile doesn't exist", finalPath).c_str() };

		std::ifstream str(finalPath);
		std::optional<T> settings;
		nlohmann::json jfile;
		str >> jfile;
		str.close();
		try
		{
			settings = jfile;
		}
		catch (...)
		{
		}
		return settings;
	}
	template<typename T>
	bool CreateFileWithSettings(const std::string& path, const T& settings)const
	{
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