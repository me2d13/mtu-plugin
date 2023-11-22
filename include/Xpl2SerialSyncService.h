#pragma once

#include <string>
#include <thread>


class Xpl2SerialSyncService {
public:
	bool start();
	bool stop();
private:
	bool m_running = false;
	std::thread m_syncThread;
	float m_lastElevatorTrimValue = 0.0f;
	void sync();
};
