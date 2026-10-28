#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* TARGET_SSID = "iPhoneLouise";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void loop() {
  int found = WiFi.scanNetworks();
  int rssi = 0;

  for (int i = 0; i < found; i++) {
    Serial.printf("  [%s] %d dBm\n", WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    if (WiFi.SSID(i) == TARGET_SSID) {
      rssi = WiFi.RSSI(i);
      break;
    }
  }

  if (rssi != 0) {
    Serial.printf("Detected! RSSI: %d dBm\n", rssi);
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("Not detected");
    digitalWrite(LED_BUILTIN, HIGH);
  }

  delay(2000);
}