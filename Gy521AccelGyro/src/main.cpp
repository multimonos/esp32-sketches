#include <Arduino.h>
#include <esp_log.h>

void setup() { Serial.begin(115200); }

void loop() {
  Serial.println("ohai :)");
  delay(1000);
}
