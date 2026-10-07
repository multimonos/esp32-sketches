#include "esp32-hal-adc.h"
#include "esp32-hal-ledc.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

const uint8_t POT_GPIO = 36;
const uint8_t LED_GPIO = 32;
const uint8_t PWM_CHANNEL = 0;

void setup() {
  Serial.begin(115200);

  ledcAttachPin(LED_GPIO, PWM_CHANNEL);
  ledcSetup(PWM_CHANNEL, 12000, 8);
}

void loop() {
  // Expect range = [0, 4095] for 12 bit resolution on SENSOR_VP ( gpio36 ).
  uint16_t value = analogRead(POT_GPIO);

  // map brightness
  uint8_t brightness = (value * 255) / 4095;

  // power led
  ledcWrite(PWM_CHANNEL, brightness);

  // log
  Serial.printf("\nraw: %d, brightness: %d", value, brightness);

  delay(100);
}
