#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "WifiConnection.h"
#include "WifiScanner.h"
#include "Proximity.h"
#include "LedIndicator.h"
#include "WebDashboard.h"

const char* TARGET_SSID = "iPhoneLouise";

WifiScanner scanner(TARGET_SSID);
ProximityClassifier classifier;
LedIndicator led(LED_BUILTIN, true);
WebDashboard dashboard(scanner, classifier);

bool dashboardReady = false;
Zone lastZone = Zone::Away;

void setup() {
  Serial.begin(115200);
  led.begin();

  Serial.println("Connecting to Wi-Fi...");
    if (!WifiConnection::connect(WIFI_SSID, WIFI_PASSWORD)) 
    {
        Serial.println("Wi-Fi connection failed, check secrets.h (LED still works)");
        return;
    }

    dashboardReady = dashboard.begin();
    if (!dashboardReady) {
        Serial.println("LittleFS mount failed, upload the filesystem image");
        return;
    }

    Serial.print("Dashboard: http://");
    Serial.println(WiFi.localIP());
}

void loop() {
  scanner.update();

    Zone zone = classifier.classify(scanner.isDetected(), scanner.getRssi());
    led.show(zone);

    if (zone != lastZone) {
        Serial.printf("Zone: %s (%d dBm)\n", zoneToString(zone), scanner.getRssi());
        lastZone = zone;
    }

    if (dashboardReady) {
        dashboard.handleClient();
    }
}