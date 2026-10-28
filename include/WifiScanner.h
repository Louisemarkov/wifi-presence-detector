#pragma once
#include <Arduino.h>
#include "interface/IPresenceSource.h"

// Class the detects a device by looking for its SSID in Wi-Fi scans
class WifiScanner : public IPresenceSource 
{

    private: void startScan();
    private: void processResults(int networkCount);

    private: String _targetSsid;
    private: bool _detected = false;
    private: int _rssi = 0;

    public:  explicit WifiScanner(const String& targetSsid);

    public:  void update();
    public:  bool isDetected() const override;
    public:  int getRssi() const override;
};