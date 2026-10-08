#include "esp32-hal-gpio.h"
#include "esp32-hal.h"
#include "esp_attr.h"
#include "freertos/portmacro.h"
#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

/**
 * Why use mutex lock here?
 *
 * Consider that the int interruptCount might be 32-bits.  It's
 * possible that onInterrupt() writes 16 of the bits,
 */
constexpr uint8_t LED_GPIO = 32;
constexpr uint8_t INTERRUPT_GPIO = 25;
constexpr uint32_t DEBOUNCE_MICROS = 1000000; // 1s

/** Interrupt Service Routine setup */
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

bool ledEnabled = false;

// "volatile" is required to modify the value within the ISR function.
volatile int interruptCount = 0;
uint8_t toggleCount = 0;
volatile unsigned long lastMicros = 0;

// ISR Handler
void IRAM_ATTR onInterrupt() {

  uint32_t now = micros(); // call once outside critical

  // Acquire mutex lock
  // Temporarily disable interrupts on the current cpu core
  portENTER_CRITICAL_ISR(&mux);

  // If it's been a second
  if (now - lastMicros >= DEBOUNCE_MICROS) {
    interruptCount++;
    lastMicros = now;
  }

  portEXIT_CRITICAL_ISR(&mux);
}

void setup() {
  Serial.begin(115200);

  /** LED setup */
  // ledcSetup(0,12000,8);
  // ledcAttachPin(LED_GPIO,0);
  pinMode(LED_GPIO, OUTPUT);

  /** Button with interrupt setup */

  // Using internal pullup insteadof hardwired resistor.
  pinMode(INTERRUPT_GPIO, INPUT_PULLUP);

  // Attach an interrupt to the gpio pin.
  // Trigger the interrupt on the falling edge of the press
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_GPIO), onInterrupt, FALLING);
}

void loop() {
  // IO Control
  bool shouldToggle = false;

  // Write data then release lock
  portENTER_CRITICAL(&mux);
  if (interruptCount > 0) {
    interruptCount--;
    shouldToggle = true;
  }
  portEXIT_CRITICAL(&mux);

  // Use the bool test here so that io ops
  // are not performed within critical code
  if (shouldToggle) {
    toggleCount++;
    ledEnabled = !ledEnabled;
    digitalWrite(LED_GPIO, ledEnabled);
    Serial.printf("\ninterrupt triggered: %d", toggleCount);
  }
}
