#include <Arduino.h>

#include "ESP8266WiFi.h"
#include "WiFiClient.h"


void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Disable light sleep");
  wifi_set_sleep_type(NONE_SLEEP_T);
  delay(2000);

  Serial.println("Enable light sleep");
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  delay(2000);
}