#include "Proximity.h"

ProximityClassifier::ProximityClassifier(ProximityThresholds thresholds)
    : _thresholds(thresholds) {}

Zone ProximityClassifier::classify(bool detected, int rssi) const 
{
    Zone zone = Zone::Far;

    if (!detected) 
    {
        zone = Zone::Away;
    } 
    
    else if (rssi > _thresholds.near) 
    {
        zone = Zone::Near;
    } 
    
    else if (rssi > _thresholds.medium) 
    {
        zone = Zone::Medium;
    }

    return zone;
}

const char* zoneToString(Zone zone)
{
    const char* name = "away";

    switch (zone) 
    {
        case Zone::Near:name = "near";
        break;

        case Zone::Medium:name = "medium";
        break;

        case Zone::Far:name = "far";
        break;

        default:
        break;
    }

    return name;
}