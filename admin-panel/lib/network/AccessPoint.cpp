#include "AccessPoint.h"

AP ap;

AP::AP(String _ssid, String _password = "")
{
	ssid = _ssid;
	password = _password;
	ap_status = OFF;
}

bool AP::init()
{
	ap_status = STARTING;

	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(ap_ip, ap_ip, IPAddress(255, 255, 255, 0));

	if (WiFi.softAP(&ssid, &password))
	{
		if (!(getDNS().start(53, "*", ap_ip)))
		{
			tools::error("DNS Fail!");
			ap_status = ERROR;
		}

		tools::log("DNS Success");
		ap_status = ON;
		return true;
	}
	else
	{
		ap_status = ERROR;
		return false;
	}
}

void AP::info()
{
	WiFi.printDiag(Serial);
}