#include "esp32-hal-touch.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

/**
 * Touch Sensor
 *
 * touch / capcitive sensor is natively available
 * on gpios = [ 32, 33, 27, 14, 12, 13, 4, 0 , 2, 15 ]
 */
constexpr uint8_t TOUCH_GPIO = 32;

void setup() { Serial.begin(115200); }

void loop() {
  uint16_t val = touchRead(TOUCH_GPIO);
  Serial.printf("\nvalue: %d", val);
  delay(100);
}
