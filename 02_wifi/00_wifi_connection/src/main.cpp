#include <Arduino.h>
#include <WiFi.h>

#include "./wifi-info.h"

const char SSID[] = WIFI_SSID; // "xxxx"
const char PASSWORD[] = WIFI_PASSWORD; // "xxxx"

void setup() {
  Serial.begin(115200);
  while(!Serial);

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("Connecting to the WiFi AP: %s ", SSID);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
