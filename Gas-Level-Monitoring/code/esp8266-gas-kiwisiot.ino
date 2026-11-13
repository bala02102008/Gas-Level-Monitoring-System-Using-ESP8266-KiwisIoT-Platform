/*
  Gas Level Monitoring System - ESP8266 NodeMCU + MQ-2 + KiwisIoT
  Reads the MQ-2 analog output on A0 and sends the raw value to
  KiwisIoT Channel 0 (shown on a Gauge widget).

  NOTE: Replace the placeholders below with your own details.
  Never upload real Wi-Fi credentials to a public repository.
*/

#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

const char* ssid  = "YOUR_WIFI_NAME";
const char* pass  = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_DASHBOARD_TOPIC_ID";   // e.g. dash_xxxxxxxxxxxxx

#define GAS_SENSOR_PIN A0

KiwisIoT kiwisiot(ssid, pass, topic);

void sendGasData() {
  int gasValue = analogRead(GAS_SENSOR_PIN);

  Serial.println();
  Serial.println("---------- GAS MONITORING ----------");
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  String gasData = String(gasValue);
  kiwisiot.send("0", gasData);

  Serial.print("Sent to KiwisIoT Channel 0: ");
  Serial.println(gasData);
}

void setup() {
  Serial.begin(115200);
  kiwisiot.begin();
}

void loop() {
  kiwisiot.loop();
  sendGasData();
  delay(2000);
}
