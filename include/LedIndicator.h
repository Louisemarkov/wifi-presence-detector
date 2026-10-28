#pragma once
#include <Arduino.h>
#include "Proximity.h"

// Blink interval in ms for each zone
struct BlinkIntervals 
{
    unsigned long near = 100;
    unsigned long medium = 400;
    unsigned long far = 1000;
};

// Class that shows the current zone by blinking an LED, off when away
class LedIndicator 
{

    private: unsigned long intervalFor(Zone zone) const;
    private: void setLed(bool on);

    private: uint8_t _pin;
    private: bool _activeLow;
    private: BlinkIntervals _intervals;
    private: unsigned long _lastToggle = 0;
    private: bool _isOn = false;

    public:  LedIndicator(uint8_t pin, bool activeLow, BlinkIntervals intervals = {});

    public:  void begin();
    public:  void show(Zone zone);
};