#include "AccessPoint.h"

IPAddress local_IP(192, 168, 1, 1);
AP ap("Coexist WiFi", "", local_IP);

AP::AP(String _ssid, String _password, IPAddress _ip)
{
	ssid = _ssid;
	password = _password;
	ap_ip = _ip;
	ap_status = OFF;
}

bool AP::init()
{
	tools::log("Starting AP...");
	ap_status = STARTING;

	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(ap_ip, ap_ip, IPAddress(255, 255, 255, 0));

	tools::log(WiFi.softAPIP().toString());
	tools::log(WiFi.softAPBroadcastIP().toString());
	tools::log(WiFi.broadcastIP().toString());
	tools::log(WiFi.gatewayIP().toString());

	if (WiFi.softAP(ssid, password))
	{
		if (!(router.dnsServer.start(53, "*", ap_ip)))
		{
			tools::error("DNS Fail!");
			ap_status = ERROR;
		}
		tools::log(WiFi.dnsIP().toString());
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