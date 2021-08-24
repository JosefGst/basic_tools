#include <Arduino.h>

/**
 * An example showing how to put ESP8266 into Deep-sleep mode
 * connect RST with D0 for wake up
 */
 
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }
  Serial.println();
  Serial.println();
  Serial.println("I'm awake.");
  delay(5000);
  
  Serial.println("Going into deep sleep for 20 seconds");
  ESP.deepSleep(5e6); // 20e6 is 20 microseconds
}

void loop() {
}