#pragma once

#include <string>
#include "serialib.h"
#include <deque>
#include <thread>


class SerialService {
public:
	bool connect(std::string comPort);
	bool shutdown();
	std::deque<std::string>& getReceivedMessages() { return m_receivedMessages; }
	bool writeData(std::string message);
private:
	std::string m_comPort;
	serialib m_serial;
	bool m_connected = false;
	std::deque<std::string> m_receivedMessages;
	std::thread m_readThread;
	void readData();
	const int maxMessages = 100;
};
