#pragma once
#include <ESP8266WebServer.h>
#include "interface/IPresenceSource.h"
#include "Proximity.h"

// Class that serves the web files from flash and a JSON status endpoint
class WebDashboard 
{
    private: void handleStatus();
    private: String buildStatusJson() const;

    private: ESP8266WebServer _server;
    private: const IPresenceSource& _source;
    private: const ProximityClassifier& _classifier;

    public:  WebDashboard(const IPresenceSource& source, const ProximityClassifier& classifier, uint16_t port = 80);

    public:  bool begin();
    public:  void handleClient();
};