#include "WifiScanner.h"
#include <ESP8266WiFi.h>

WifiScanner::WifiScanner(const String& targetSsid) : _targetSsid(targetSsid) {}

void WifiScanner::update() 
{
    int result = WiFi.scanComplete();

    if (result >= 0) 
    {
        processResults(result);
        WiFi.scanDelete();
        startScan();
    } 
    else if (result == WIFI_SCAN_FAILED) 
    {
        startScan(); // no scan running yet, or the last one failed
    }
}

void WifiScanner::startScan() 
{
    WiFi.scanNetworks(true); // true = scan in the background
}

void WifiScanner::processResults(int networkCount) 
{
    _detected = false;
    _rssi = 0;

    for (int i = 0; i < networkCount && !_detected; i++) 
    {
        if (WiFi.SSID(i) == _targetSsid) 
        {
            _detected = true;
            _rssi = WiFi.RSSI(i);
        }
    }
}

bool WifiScanner::isDetected() const 
{ 
    return _detected; 
}

int WifiScanner::getRssi() const 
{ 
    return _rssi; 
}