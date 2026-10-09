#include "esp32-hal-ledc.h"
#include "esp32-hal-touch.h"
#include "esp_attr.h"
#include "freertos/portmacro.h"
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

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile bool touchDetected = false;

void IRAM_ATTR onTouch() {
  portENTER_CRITICAL_ISR(&mux);
  touchDetected = true;
  portEXIT_CRITICAL_ISR(&mux);
}

void setup() {
  Serial.begin(115200);
  ledcSetup(0, 12000, 8);
  ledcAttachPin(LED_GPIO, 0);
  touchAttachInterrupt(TOUCH_GPIO, onTouch, TOUCH_THRESHOLD);
}

void loop() {

  bool takeAction = false;

  portENTER_CRITICAL(&mux);
  takeAction = touchDetected;
  touchDetected = false; // reset after consumption
  portEXIT_CRITICAL(&mux);

  if (takeAction) {
    ledcWrite(0, 255);
  } else {
    ledcWrite(0, 0);
  }

  // this delay is the "latch duration" as touchDeteced is
  // only reset to false once per loop
  delay(50);
}
