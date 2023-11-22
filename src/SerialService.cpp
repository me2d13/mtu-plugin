#include <string>
#include "SerialService.h"
#include <plog/Log.h>

bool SerialService::connect(std::string comPort) {
	m_comPort = comPort;
	if (m_serial.openDevice(m_comPort.c_str(), 115200) != 1) {
		PLOGE << "Failed to open serial port " << m_comPort;
		return false;
	}
	m_connected = true;
	PLOGD << "Opened serial port " << m_comPort;

	// start thread to read data
	m_readThread = std::thread(&SerialService::readData, this);

	// send hello message
	writeData("{\"command\":\"hello\"}\n");

	return true;
}

bool SerialService::shutdown() {
	if (m_connected) {
		m_serial.closeDevice();
		m_connected = false;
	}
	if (m_readThread.joinable()) {
		m_readThread.join();
	}
	return true;
}

void SerialService::readData() {
	while (m_connected) {
		char buf[1024];
		int bytesRead = m_serial.readString(buf, '\n', 1023, 100);
		if (bytesRead > 0) {
			std::string message(buf, bytesRead);
			PLOGD << "Received message: " << message;
			// if queue is full, remove the oldest message
			if (m_receivedMessages.size() >= maxMessages)
				m_receivedMessages.pop_front();
			m_receivedMessages.push_back(message);
		}
	}
}

bool SerialService::writeData(std::string message) {
	if (m_connected) {
		PLOGD << "Sending message: " << message;
		m_serial.writeString(message.c_str());
		return true;
	}
	else {
		PLOGE << "Serial port not connected";
		return false;
	}
}