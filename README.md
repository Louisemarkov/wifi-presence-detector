# wifi presence detector

Small project with a WeMos D1 (ESP8266) that detects when my phone is nearby

It scans the Wi-Fi networks around it every 2 seconds and looks for my phone's hotspot
If it finds it the LED turns on and it prints the signal strength (RSSI)
The closer the phone is the stronger the signal so it also gives a rough idea of distance

## what I used
- WeMos D1 (ESP8266)
- micro-USB cable
- VS Code + PlatformIO

## how to run it
1. open the project in VS Code with PlatformIO
2. change `TARGET_SSID` in `src/main.cpp` to your hotspot name (careful, it's case sensitive, I got stuck on that)
3. upload and open the serial monitor at 115200

phone next to the board: around -37 dBm
phone in another room: around -73 dBm