#pragma once

#include <string>

class Config
{
private:
	std::string comPort;
	std::string configPath;
	int serverPort;
public:
	Config() : configPath("."), comPort(), serverPort(8080) {};
	bool readConfigFile(std::string pConfigPath);
	std::string getComPort();
	int getServerPort();
	std::string getConfigPath();
};

Config* getConfig();