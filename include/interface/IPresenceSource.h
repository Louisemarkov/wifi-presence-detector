#pragma once

// Class that can tell if the target device is nearby
class IPresenceSource 
{

    public:  virtual ~IPresenceSource() = default;
    public:  virtual bool isDetected() const = 0;
    public:  virtual int getRssi() const = 0;
    
};