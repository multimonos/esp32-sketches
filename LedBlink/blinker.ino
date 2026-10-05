
const uint8_t LED_GPIO = 33;

void setup() {
  pinMode(LED_GPIO, OUTPUT);    // assign led to pin
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_GPIO, HIGH);
    delay(250);
    digitalWrite(LED_GPIO, LOW);
    delay(500);
  }

  delay(1500);
}
