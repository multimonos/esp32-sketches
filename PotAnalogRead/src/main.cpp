#include "esp32-hal-adc.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

const uint8_t POT_GPIO = 36;

void setup() { Serial.begin(115200); }

void loop() {
  // Expect range = [0, 4095] for 12 bit resolution on SENSOR_VP ( gpio36 ).
  uint16_t value = analogRead(POT_GPIO);

  // Expect range = [0, 3.3] volts for this board when using the `3V3` pin.
  uint32_t milliVolts = analogReadMilliVolts(POT_GPIO);

  Serial.printf("\nraw: %d, milliVolts: %d mV", value, milliVolts);

  delay(100);
}
