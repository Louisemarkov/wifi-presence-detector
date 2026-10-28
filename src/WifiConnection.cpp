#include "WifiConnection.h"
#include <ESP8266WiFi.h>

bool WifiConnection::connect(const char* ssid, const char* password, unsigned long timeoutMs) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - start < timeoutMs) 
    {
        delay(500);
    }

    return WiFi.status() == WL_CONNECTED;
}