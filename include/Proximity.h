#pragma once

enum class Zone { Away, Far, Medium, Near };

// RSSI limits in dBm for each zone
struct ProximityThresholds 
{
    int near = -50;
    int medium = -70;
};

// Class the turns a signal strength into a distance zone
class ProximityClassifier 
{

    private: ProximityThresholds _thresholds;

    public:  explicit ProximityClassifier(ProximityThresholds thresholds = {});

    public:  Zone classify(bool detected, int rssi) const;
};

const char* zoneToString(Zone zone);