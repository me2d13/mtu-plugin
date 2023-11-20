#pragma once

#include "XPLMDataAccess.h"
#include <string>

#define DR_ELEVATOR_TRIM "sim/flightmodel2/controls/elevator_trim"
#define DR_AIRCRAFT "sim/aircraft/view/acf_descrip"


class XplData {
private:
	XPLMDataRef elevatorTrimDr;
	XPLMDataRef aircraftDr;
	float elevatorTrimValue{ 0.0 };
	std::string aircraft{ "" };
	bool inFlight{ false };
public:
	void init();
	void update();
	float getElevatorTrimValue() { return elevatorTrimValue; }
	void onPluginReceiveMessage(XPLMPluginID inFromWho, int	inMessage, void* inParam);
	std::string getAircraft() { return aircraft; }
	bool isInFlight() { return inFlight; }
};

