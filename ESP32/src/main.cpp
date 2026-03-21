#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "ota.h"

#define WIFI_SSID "DvorNet"
#define WIFI_PASS "dvor62tuc"

WebServer server(80);

void handleRoot() {
  String html = "<html><head><meta charset='UTF-8'><meta http-equiv='refresh' content='5'></head>";
  html += "<body style='font-family:sans-serif; text-align:center; padding:50px;'>";
  html += "<h1>Inverter Dashboard</h1>";
  html += "<div style='font-size:24px; margin:20px; border:2px solid #333; padding:20px; display:inline-block;'>";
  html += "<b>Battery Power:</b> Updated<br>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Pripojuji WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi OK: " + WiFi.localIP().toString());

    server.on("/", handleRoot);
    server.begin();

    OTA::check();
}

void loop() {
    OTA::check();
    server.handleClient();
    delay(2000); // kontroluj každých 60s
}