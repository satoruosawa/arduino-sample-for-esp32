#include "time.h"
#include <Arduino.h>
#include <WiFi.h>

#include "./wifi-info.h"

const char * SSID = WIFI_SSID; // "xxxx"
const char * PASSWORD = WIFI_PASSWORD; // "xxxx"
const char * NTP_SERVER = "ntp.nict.jp";

const long GMT_OFFSET_SEC = 9 * 3600; // +9hours
const int DAYLIGHT_OFFSET_SEC = 0; // summer time offset

void PrintLocalTime();

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

  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  PrintLocalTime();
}

void loop() {
  PrintLocalTime();
  delay(1000);
}

void PrintLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%Y %m %d %a %H:%M:%S");
  Serial.println(
    String(timeinfo.tm_year + 1900) + "/" +
    String(timeinfo.tm_mon + 1) + "/" +
    String(timeinfo.tm_mday) + " " +
    String(timeinfo.tm_hour) + ":" +
    String(timeinfo.tm_min) + ":" +
    String(timeinfo.tm_sec)
  );
}
