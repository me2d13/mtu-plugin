#include "XplData.h"
#include <plog/Log.h>


void XplData::init()
{
	// find dataref for elevator trim
	elevatorTrimDr = XPLMFindDataRef(DR_ELEVATOR_TRIM);
	if (elevatorTrimDr == NULL)
	{
		PLOGE << "XplData::init() - elevator trim dataref not found";
	}
}

void XplData::update()
{
	// read dataref for elevator trim
	elevatorTrimValue = XPLMGetDataf(elevatorTrimDr);
}

float XplData::getElevatorTrimValue()
{
	return elevatorTrimValue;
}