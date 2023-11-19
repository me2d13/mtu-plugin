#include "Config.h"

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include <plog/Log.h>

bool Config::readConfigFile(std::string pConfigPath)
{
	configPath = pConfigPath;
	// read a JSON file if it exists
	std::string fullPath = configPath + "\\config.json";
	std::ifstream i(fullPath);
	if (!i.is_open())
	{
		PLOGE << fullPath << " not found";
		return false;
	}
	PLOGD << "Reading config from " << fullPath;
	nlohmann::json j;
	try {
		i >> j;
		comPort = j.value("port", "COM1");
		serverPort = j.value("serverPort", 8080);
	}
	catch (nlohmann::json::exception& e) {
		PLOGE << "Error reading config.json: " << e.what();
		return false;
	}
	// close the file
	i.close();
	// print the values read from the JSON file
	PLOGD << "COM port: " << comPort;
	PLOGD << "Server port: " << serverPort;
	return true;
}

std::string Config::getComPort()
{
	return comPort;
}

int Config::getServerPort()
{
	return serverPort;
}

std::string Config::getConfigPath()
{
	return configPath;
}