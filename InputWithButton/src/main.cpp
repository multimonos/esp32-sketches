#include <Arduino.h>
#include <cstdint>
#include <esp_log.h>

/**
 * In this sketch the input at pin 32 reads the high-low value.  If switch is
 * open then LO if closed then HIGH.  For a HIGH read then we write HIGH to
 * 36 which sends 3.3V to the LED circuit otherwise we write LOW.
 */
const uint8_t LED_GPIO = 32;
const uint8_t BUTTON_GPIO = 36;

int isPressed = 0;

void setup() {

  pinMode(BUTTON_GPIO, INPUT);

  pinMode(LED_GPIO, OUTPUT);

  Serial.begin(115200);
  Serial.println("Should light the LED when button is pressed ...");
}

void loop() {
  isPressed = digitalRead(BUTTON_GPIO);

  if (isPressed == HIGH) {
    digitalWrite(LED_GPIO, HIGH);
  } else {
    digitalWrite(LED_GPIO, LOW);
  }

  Serial.printf("isPressed: %d\n", isPressed);

  delay(50);
}
