#include "esp32-hal-adc.h"
#include "esp32-hal-ledc.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

const uint8_t POT0_GPIO = 39;
const uint8_t POT1_GPIO = 36;

const uint8_t RED_GPIO = 32;
const uint8_t RED_CHANNEL = 0;

const uint8_t BLU_GPIO = 33;
const uint8_t BLU_CHANNEL = 1;

void setup() {
  Serial.begin(115200);

  ledcAttachPin(RED_GPIO, RED_CHANNEL);
  ledcSetup(RED_CHANNEL, 12000, 8);

  ledcAttachPin(BLU_GPIO, BLU_CHANNEL);
  ledcSetup(BLU_CHANNEL, 12000, 8);
}

void loop() {
  // Expect range = [0, 4095] for 12 bit resolution on SENSOR_VP ( gpio36 ).
  uint16_t redRaw = analogRead(POT0_GPIO);
  uint16_t bluRaw = analogRead(POT1_GPIO);

  // map brightness
  uint8_t redValue = (redRaw * 255) / 4095;
  uint8_t bluValue = (bluRaw * 255) / 4095;

  // power led
  ledcWrite(RED_CHANNEL, redValue);
  ledcWrite(BLU_CHANNEL, bluValue);

  // log
  Serial.printf("\nred: raw: %d, value: %d -- blu: raw: %d, value: %d", redRaw,
                redValue, bluRaw, bluValue);

  delay(100);
}
