#include "esp32-hal-adc.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

constexpr uint8_t READ_GPIO = 39;

void setup() { Serial.begin(115200); }

void loop() {
  uint16_t val = analogRead(READ_GPIO);
  Serial.printf("\nvalue: %d", val);
  delay(100); // not really optimal way to use hardware
}
