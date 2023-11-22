#pragma once

#include "Config.h"
#include "XplData.h"
#include "SerialService.h"
#include "Xpl2SerialSyncService.h"

class Globals
{
private:
	Config config;
	XplData xplData;
	SerialService serialService;
	Xpl2SerialSyncService xpl2SerialSyncService;
public:
	Config* getConfig() { return &config; }
	XplData* getXplData() { return &xplData;}
	SerialService* getSerialService() { return &serialService; }
	Xpl2SerialSyncService* getXpl2SerialSyncService() { return &xpl2SerialSyncService; }
};

Globals* glb();