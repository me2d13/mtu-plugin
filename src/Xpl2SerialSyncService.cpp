#include "Xpl2SerialSyncService.h"
#include <plog/Log.h>
#include <thread>
#include "global.h"
#include "json.hpp"


bool Xpl2SerialSyncService::start()
{
	if (m_running)
		return false;
	m_running = true;
	m_syncThread = std::thread(&Xpl2SerialSyncService::sync, this);
	return true;
}

bool Xpl2SerialSyncService::stop()
{
	if (!m_running)
		return false;
	m_running = false;
	if (m_syncThread.joinable())
		m_syncThread.join();
	return true;
}

void Xpl2SerialSyncService::sync()
{
	while (m_running)
	{
		// check if we are in flight
		if (glb()->getXplData()->isInFlight())
		{
			// check if elevator trim has changed
			float elevatorTrimValue = glb()->getXplData()->getElevatorTrimValue();
			if (elevatorTrimValue != m_lastElevatorTrimValue)
			{
				// send elevator trim value to serial port as JSON
				nlohmann::json j;
				j["command"] = "setPositions";
				// convert elevator trim value with range -1.0 to 1.0 to range 0 to 100.0 and round to 1 decimal place
				float elevatorTrimValueForJson = roundf((elevatorTrimValue + 1.0f) * 50.0f * 10.0f) / 10.0f;
				j["positions"]["elevatorTrim"] = elevatorTrimValueForJson;
				std::string message = j.dump() + "\n";
				glb()->getSerialService()->writeData(message);
				m_lastElevatorTrimValue = elevatorTrimValue;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}