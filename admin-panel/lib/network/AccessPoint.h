#pragma once

#include "Network.h"

class AP : public Network
{
private:
	String ssid;
	String password;
	IPAddress ap_ip;

public:
	/**
	 * @brief Access Point Instance Constructor
	 * @param ssid AP SSID
	 * @param password (optional) AP Password
	 */
	AP(String _ssid, String _password = "");

	/**
	 * @brief Turns on Access Point
	 * @return Status boolean
	 */
	bool init();

	/**
	 * @brief Prints WiFi info
	 */
	void info();
};

extern AP ap;