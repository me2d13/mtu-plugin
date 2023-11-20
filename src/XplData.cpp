#include "XplData.h"
#include <plog/Log.h>
#include "XPLMPlugin.h"


void XplData::init()
{
	// find dataref for elevator trim
	elevatorTrimDr = XPLMFindDataRef(DR_ELEVATOR_TRIM);
	if (elevatorTrimDr == NULL)
	{
		PLOGE << "XplData::init() - elevator trim dataref not found";
	}
	// find dataref for aircraft
	aircraftDr = XPLMFindDataRef(DR_AIRCRAFT);
	if (aircraftDr == NULL)
	{
		PLOGE << "XplData::init() - aircraft dataref not found";
	}
}

void XplData::update()
{
	// read dataref for elevator trim
	elevatorTrimValue = XPLMGetDataf(elevatorTrimDr);
	// read dataref for aircraft
	char aircraftBuf[256];
	XPLMGetDatab(aircraftDr, aircraftBuf, 0, 256);
	aircraftBuf[255] = '\0'; // ensure null termination
	aircraft = std::string(aircraftBuf);
}

void XplData::onPluginReceiveMessage(XPLMPluginID inFromWho, int	inMessage, void* inParam)
{
	int planeIndex = (int)inParam;
	switch (inMessage)
	{
	case XPLM_MSG_PLANE_LOADED:
		PLOGD << "XplData::onPluginReceiveMessage() - XPLM_MSG_PLANE_LOADED with index " << planeIndex;
		if (planeIndex == 0) {
			inFlight = true;
		}
		break;
	case XPLM_MSG_PLANE_UNLOADED:
		PLOGD << "XplData::onPluginReceiveMessage() - XPLM_MSG_PLANE_UNLOADED with index " << planeIndex;
		if (planeIndex == 0) {
			inFlight = false;
		}
		break;
	default:
		break;
	}
}