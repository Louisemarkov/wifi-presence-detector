#pragma once

// Connects the board to a Wi-Fi network
namespace WifiConnection 
{
    // Blocks until connected returns false after the timeout
    bool connect(const char* ssid, const char* password, unsigned long timeoutMs = 20000);
}