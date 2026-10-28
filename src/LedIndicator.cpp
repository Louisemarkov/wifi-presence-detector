#include "LedIndicator.h"

LedIndicator::LedIndicator(uint8_t pin, bool activeLow, BlinkIntervals intervals)
    : _pin(pin), _activeLow(activeLow), _intervals(intervals) {}

void LedIndicator::begin() {
    pinMode(_pin, OUTPUT);
    setLed(false);
}

void LedIndicator::show(Zone zone) 
{
    unsigned long interval = intervalFor(zone);

    if (interval == 0) 
    {
        setLed(false);
    } 
    
    else if (millis() - _lastToggle >= interval) 
    {
        _lastToggle = millis();
        setLed(!_isOn);
    }
}

unsigned long LedIndicator::intervalFor(Zone zone) const 
{
    unsigned long interval = 0; // being away = LED off

    switch (zone) 
    {
        case Zone::Near:interval = _intervals.near;
        break;

        case Zone::Medium:interval = _intervals.medium;
        break;

        case Zone::Far:interval = _intervals.far;
        break;

        default:
        break;
    }

    return interval;
}

void LedIndicator::setLed(bool on) 
{
    _isOn = on;
    digitalWrite(_pin, (on != _activeLow) ? HIGH : LOW);
}