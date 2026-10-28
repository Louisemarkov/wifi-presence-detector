#include "WebDashboard.h"
#include <LittleFS.h>

WebDashboard::WebDashboard(const IPresenceSource& source, const ProximityClassifier& classifier, uint16_t port)
    : _server(port), _source(source), _classifier(classifier) {}

bool WebDashboard::begin() {
    bool mounted = LittleFS.begin();

    if (mounted) {
        _server.on("/status", [this]() { handleStatus(); });

        // Static files from the data/ folder
        _server.serveStatic("/", LittleFS, "/index.html");
        _server.serveStatic("/style.css", LittleFS, "/style.css");
        _server.serveStatic("/app.js", LittleFS, "/app.js");

        _server.begin();
    }

    return mounted;
}

void WebDashboard::handleClient() {
    _server.handleClient();
}

void WebDashboard::handleStatus() {
    _server.send(200, "application/json", buildStatusJson());
}

String WebDashboard::buildStatusJson() const {
    bool detected = _source.isDetected();
    int rssi = _source.getRssi();
    Zone zone = _classifier.classify(detected, rssi);

    String json = "{";
    json += "\"detected\":" + String(detected ? "true" : "false") + ",";
    json += "\"rssi\":" + String(rssi) + ",";
    json += "\"zone\":\"" + String(zoneToString(zone)) + "\"";
    json += "}";
    return json;
}