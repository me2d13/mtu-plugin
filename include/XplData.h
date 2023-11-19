#pragma once

#include "XPLMDataAccess.h"

#define DR_ELEVATOR_TRIM "sim/flightmodel2/controls/elevator_trim"


class XplData {
private:
	XPLMDataRef elevatorTrimDr;
	float elevatorTrimValue{ 0.0 };
public:
	void init();
	void update();
	float getElevatorTrimValue();
};

