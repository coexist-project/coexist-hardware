#include "OurServer.h"

AsyncWebServer * webServer = new AsyncWebServer(80);

bool sv::InitServerWeb(const char * _index)
{
    webServer->serveStatic("/", LittleFS, "/").setDefaultFile(_index);

    webServer->onNotFound([](AsyncWebServerRequest *request)
                      { request->send(400, "text/plain", request->url() + "Not found"); });

    webServer->on("/assets", HTTP_GET, sv::handleAssets);

    webServer->on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", sv::ScanNetworks()); });

    webServer->on("/data", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", sv::ScanData()); });

    webServer->begin();

    return true;
}

String sv::ScanData()
{
    Dir dir = LittleFS.openDir("/");

    if (dir.isDirectory())
    {
        File file = dir.openFile("r");
        Serial.print(file.name());
    }
    while (dir.next())
    {
        Serial.println("Name: " + dir.fileName());
        Serial.println("Size: " + dir.fileSize());
    }

    return "Showed dir";
}

String sv::ScanNetworks()
{
    String str[8];

    int cantOfNetworks = WiFi.scanNetworks();
    Serial.println(cantOfNetworks);

    for (int i = 0; i < cantOfNetworks; i++)
    {
        bool *nameOfNetwork = new bool(false);
        for (String nameNetwork : str)
        {
            if (nameNetwork == WiFi.SSID(i))
            {
                *nameOfNetwork = true;
                break;
            }
        }

        if (!(*nameOfNetwork))
        {
            str[i] += WiFi.SSID(i);
            Serial.println(str[i]);
        }
    }

    Serial.println("-------");

    String finalString = "";

    for (String name : str)
        finalString += name + " \n";
    return finalString;
}

void sv::handleAssets(AsyncWebServerRequest *request)
{
    Serial.print(request->url());
    String path = request->url();
    String contentType = "text/plain";

    if (path.endsWith(".html"))
    {
        contentType = "text/html";
    }
    else if (path.endsWith(".css"))
    {
        contentType = "text/css";
    }
    else if (path.endsWith(".js"))
    {
        contentType = "application/javascript";
    }
    else if (path.endsWith(".png"))
    {
        contentType = "image/png";
    }
    else if (path.endsWith(".gif"))
    {
        contentType = "image/gif";
    }
    else if (path.endsWith(".jpg"))
    {
        contentType = "image/jpeg";
    }
    else if (path.endsWith(".ico"))
    {
        contentType = "image/x-icon";
    }

    if (!LittleFS.exists(path))
    {
        request->send(404, "text/plain", "Not Found");
        return;
    }

    File file = LittleFS.open(path, "r");

    request->beginResponseStream(contentType, file);
    file.close();
}