#include "esp32-hal-adc.h"
#include <Arduino.h>
#include <esp_log.h>

/**
 * Hall Effect Sensor
 *
 * - wave a magnet directly over the chip to activate
 * - sensor is near gpio 32
 */
void setup() { Serial.begin(115200); }

void loop() {

  int val = hallRead();

  Serial.printf("\nhall-effect-value: %d", val);

  delay(100);
}
