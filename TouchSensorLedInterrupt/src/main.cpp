#include "esp32-hal-ledc.h"
#include "esp32-hal-touch.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>
#include <sys/types.h>

/**
 * Touch Sensor
 *
 * touch / capcitive sensor is natively available
 * on gpios = [ 32, 33, 27, 14, 12, 13, 4, 0 , 2, 15 ]
 */
constexpr uint8_t TOUCH_GPIO = 32;
constexpr uint8_t TOUCH_THRESHOLD = 25;
constexpr uint8_t LED_GPIO = 33;

bool touchDetected = false;
void onTouch() { touchDetected = true; }

void setup() {
  Serial.begin(115200);
  ledcSetup(0, 12000, 8);
  ledcAttachPin(LED_GPIO, 0);
  touchAttachInterrupt(TOUCH_GPIO, onTouch, TOUCH_THRESHOLD);
}

void loop() {

  if (touchDetected) {
    ledcWrite(0, 255);
    touchDetected = false;
  } else {
    ledcWrite(0, 0);
  }

  delay(100);
}
