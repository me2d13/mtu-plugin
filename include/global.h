#pragma once

#include "Config.h"
#include "XplData.h"
#include "SerialService.h"

class Globals
{
private:
	Config config;
	XplData xplData;
	SerialService serialService;
public:
	Config* getConfig() { return &config; }
	XplData* getXplData() { return &xplData;}
	SerialService* getSerialService() { return &serialService; }
};

Globals* glb();